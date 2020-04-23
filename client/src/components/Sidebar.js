import React from 'react';
import { Box, List } from 'grommet';

export default function Sidebar({ botConfigs, state, setState }) {
  return (
    <Box
      width="medium"
      background="black"
      align="center"
      justify="stretch"
      overflow={{ vertical: 'auto' }}
    >
      <List
        data={botConfigs.map((c) => c.name)}
        itemProps={{ [botConfigs.indexOf(state)]: { background: 'gray' } }}
        alignSelf="stretch"
        onClickItem={({datum, index}) => setState(botConfigs[index])}
      />
    </Box>
  )
}
