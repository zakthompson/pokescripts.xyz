const fs = require('fs');
const express = require('express');
const execAsync = require('../utils/execAsync');
const uuid = require('uuid');
const { configTypes } = require('../utils/constants');
const router = express.Router();

router.get('/test', (req, res) => {
  res.json({ message: 'Success!' });
});

router.get('/genhex', async (req, res) => {
  const { query } = req;
  const { target } = query;
  const configObj = { ...query };
  delete configObj.target;
  let configStr = '';

  const { m_linkCode } = configObj;

  if (m_linkCode) {
    configStr = `${configTypes.m_linkCode} m_linkCode[] = {${configObj.m_linkCode.split('').join(',')}};`;
    delete configObj.m_linkCode;
  }

  const keys = Object.keys(configObj);
  if (keys.length) {
    configStr = `${configStr}${Object.keys(configObj).map((key) => {
      return `${configTypes[key]} ${key} = ${configObj[key]}`;
    }).join(';')};`;
  }

  const folder = uuid.v1()

  try {
    console.log(configStr);
    await execAsync(`mkdir -p tmp/${folder}`);
    await execAsync(`cp -r bots/makefile bots/HORI_Descriptors bots/Joystick.h bots/LUFA bots/Config bots/${target} tmp/${folder}`);

    if (configStr.length) {
      fs.writeFileSync(`tmp/${folder}/${target}/Config.h`, configStr);
    }

    await execAsync(`cd tmp/${folder} && make TARGET=${target}`);
    res.download(`tmp/${folder}/${target}.hex`);
  } catch(e) {
    res.status(500).json({ error: e });
  }
});

router.delete('/cleartmp', async (req, res) => {
  try {
    await execAsync(`rm -r tmp/*`);
    res.status(204).send();
  } catch(e) {
    res.status(500).json({ error: e });
  }
});

module.exports = router;
