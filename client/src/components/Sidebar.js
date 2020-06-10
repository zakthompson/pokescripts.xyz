import React from 'react';
import { Box, List, Select, Text } from 'grommet';

import { dateFormatOptions, mcuOptions } from '../utils/constants';

export default function Sidebar({ botConfigs, state, setState, dateFormat, setDateFormat, mcu, setMcu }) {
  return (
    <Box
      direction="column"
      width="300px"
      background="black"
      align="center"
      justify="stretch"
      overflow={{ vertical: 'auto' }}
    >
      <Box direction="row" align="center" pad={{ top: '40px', bottom: '5px' }} flex={{ shrink: 0 }}>
        <Text margin={{ right: '10px' }}>MCU:</Text>
        <Box width="small">
          <Select
            size="xsmall"
            options={mcuOptions}
            value={mcuOptions.find((o) => o.value === mcu)}
            onChange={({ option }) => setMcu(option.value)}
            labelKey="name"
          />
        </Box>
      </Box>
      <Box direction="row" align="center" pad={{ top: '5px', bottom: '40px' }} flex={{ shrink: 0 }}>
        <Text margin={{ right: '10px' }}>Date Format:</Text>
        <Box width="xsmall">
          <Select
            size="small"
            options={dateFormatOptions}
            value={dateFormatOptions.find((o) => o.value === dateFormat)}
            onChange={({ option }) => setDateFormat(option.value)}
            labelKey="name"
          />
        </Box>
      </Box>
      <List
        data={botConfigs.map((c) => c.name)}
        itemProps={{ [botConfigs.indexOf(state)]: { background: 'gray' } }}
        alignSelf="stretch"
        onClickItem={({datum, index}) => setState(botConfigs[index])}
      />
    </Box>
  )
}
