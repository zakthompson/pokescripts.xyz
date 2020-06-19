import axios from 'axios';

export function genHex(target, configFields, dateFormat, mcu) {
  const configParams = configFields.reduce((acc, f) => {
    const { param, value } = f;
    return { ...acc, [param]: value };
  }, {});
  axios.get('/api/genhex', {
    params: {
      target,
      mcu,
      ...configParams,
      m_JP_EU_US: dateFormat,
    },
    responseType: 'blob',
  }).then((response) => {
    const url = window.URL.createObjectURL(response.data);
    const link = document.createElement('a');
    link.href = url;
    link.setAttribute('download', `${target}.hex`);
    document.body.appendChild(link);
    link.click();
  });
}
