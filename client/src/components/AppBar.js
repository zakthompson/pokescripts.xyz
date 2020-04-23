import React from 'react';
import { Box, Heading, Select, Text } from 'grommet';

import { dateFormatOptions } from '../utils/constants';

export default function AppBar({ dateFormat, setDateFormat }) {
  return (
    <Box
      tag="header"
      direction="row"
      align="center"
      justify="between"
      background="red"
      pad={{ left: 'medium', right: 'small', vertical: 'small' }}
      elevation="medium"
      style={{ zIndex: 1 }}
    >
      <Heading level="2" margin="none">Pokemon Hex Generator</Heading>
      <Box direction="row" align="center">
        <Text margin={{ horizontal: '10px' }}>Date Format:</Text>
        <Box direction="row" width="xsmall">
          <Select
            size="small"
            options={dateFormatOptions}
            value={dateFormatOptions.find((o) => o.value === dateFormat)}
            onChange={({ option }) => setDateFormat(option.value)}
            labelKey="name"
          />
        </Box>
      </Box>
    </Box>
  );
}
