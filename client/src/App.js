import React, { useState } from 'react';
import { Box, Grommet } from 'grommet';

import AppBar from './components/AppBar';
import Sidebar from './components/Sidebar';
import BotForm from './components/BotForm';
import { botConfigs } from './utils/constants';
import { genHex } from './utils/api';

const theme = {
  global: {
    colors: {
      white: '#FFFFFF',
      red: '#EE1515',
      black: '#222224',
      gray: '#F0F0F0',
      darkGray: '#666666',
      yellow: '#FFCC00',
      brand: '#222224',
      focus: '#222224',
    },
    font: {
      family: 'Open Sans',
      size: '18px',
      height: '20px',
    },
    hover: {
      background: {
        color: 'red',
        opacity: 1,
      },
    },
  },
  heading: {
    font: {
      family: 'Montserrat',
    },
    level: {
      2: {
        font: {
          weight: 900,
        },
      },
      3: {
        font: {
          weight: 600,
        },
      },
    },
  },
  select: {
    background: 'white',
    icons: {
      color: 'black',
    },
    options: {
      text: {
        size: 'small',
      },
    },
  },
};

function App() {
  const [state, setState] = useState(botConfigs[0]);
  const [dateFormat, setDateFormat] = useState(2);
  const [mcu, setMcu] = useState('atmega16u2');

  function onSubmit() {
    genHex(state.target, state.configFields, dateFormat, mcu);
  }

  return (
    <Grommet theme={theme} full>
      <Box fill>
        <AppBar dateFormat={dateFormat} setDateFormat={setDateFormat} />
        <Box direction="row" flex overflow={{ horizontal: 'hidden' }}>
          <Sidebar
            botConfigs={botConfigs}
            state={state}
            setState={setState}
            dateFormat={dateFormat}
            setDateFormat={setDateFormat}
            mcu={mcu}
            setMcu={setMcu}
          />
          <BotForm state={state} setState={setState} onSubmit={onSubmit} dateFormat={dateFormat} />
        </Box>
      </Box>
    </Grommet>
  );
}

export default App;
