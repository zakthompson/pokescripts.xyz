import React from 'react';
import {
  Box,
  Button,
  CheckBox,
  Form,
  Heading,
  ResponsiveContext,
  Select,
  Text,
  TextInput,
} from 'grommet';
import { Alert } from 'grommet-icons';

export default function BotForm({ state, setState, onSubmit, dateFormat }) {
  function handleFieldChange(param, value) {
    const index = state.configFields.findIndex((e) => e.param === param);
    setState({
      ...state,
      configFields: [
        ...state.configFields.slice(0, index),
        {
          ...state.configFields[index],
          value,
        },
        ...state.configFields.slice(index + 1, state.configFields.length),
      ],
    });
  }

  return (
    <ResponsiveContext.Consumer>
      {size => (
        <Box
          flex
          direction="row"
          align="stretch"
          justify="stretch"
          background="gray"
          overflow={{ vertical: 'auto' }}
          pad="40px"
        >
          <Box direction={`${!['large', 'xlarge', 'xxlarge'].includes(size) ? 'column' : 'row'}`} align="start">
            <Box
              direction="column"
              pad={{ left: '20px', right: !['large', 'xlarge', 'xxlarge'].includes(size) ? '20px' : '60px' }}
              flex={{ grow: 1, shrink: !['large', 'xlarge', 'xxlarge'].includes(size) ? 0 : 1 }}
            >
              <Box direction="row" flex={{ grow: 1, shrink: 0 }}>
                <Heading margin={{ top: '0px' }} level="3">{state.name}</Heading>
              </Box>
              <Box direction="column">
                <Text size="small">{state.description}</Text>
                <Heading level="4">Instructions</Heading>
                {state.instructions.map((i, index) => (
                  <CheckBox
                    key={index}
                    size="small"
                    label={(
                      <Text margin={{ vertical: '5px' }} size="small">{i}</Text>
                    )}
                  />
                ))}
                <Heading level="4">What Will the Bot Do?</Heading>
                <ul style={{ marginTop: '0px', marginBottom: '40px' }}>
                {state.botActions.map((i, index) => (
                  <li key={index} style={{ margin: '5px 0' }}><Text size="small">{i}</Text></li>
                ))}
                </ul>
              </Box>
            </Box>
            <Box
              background="white"
              width={!['large', 'xlarge', 'xxlarge'].includes(size) ? '100%' : '600px'}
              round="small"
              flex={{ grow: 0, shrink: 0 }}
              pad="25px"
              elevation="medium"
              margin={{ bottom: '40px' }}
            >
              <Heading level="4" margin={{ top: '0px' }}>Configuration</Heading>
              <Form onSubmit={onSubmit}>
                {state.configFields.map((f) => (
                  <Box
                    key={f.param}
                    direction="row"
                    align="center"
                    justify="between"
                    pad={{ vertical: "20px" }}
                    border={{ color: 'gray', size: 'small', side: 'bottom' }}
                    flex
                  >
                    <Box width="70%" direction="column" gap="small">
                      <Text>{f.name}:</Text>
                      {f.description && (
                        <Text
                          size="small"
                          color="darkGray"
                        >
                          {f.description}
                        </Text>
                      )}
                      {f.warning && (
                        <Box
                          direction="row"
                          round="xsmall"
                          background="red"
                          pad="5px"
                          gap="small"
                        >
                          <Box pad={{ top: '3px' }}>
                            <Alert size="small" color="yellow" />
                          </Box>
                          <Text
                            size="small"
                            weight="bold"
                            color="yellow"
                          >
                            {f.warning}
                          </Text>
                        </Box>
                      )}
                    </Box>
                    {f.type === 'select' && (
                      <Box direction="row" width="xsmall">
                        <Select
                          size="small"
                          options={f.options}
                          value={f.options.find((o) => o.value === f.value)}
                          labelKey="name"
                          onChange={({ option }) => handleFieldChange(f.param, option.value)}
                        />
                      </Box>
                    )}
                    {f.type === 'bool' && (
                      <CheckBox
                        checked={f.value === 'true'}
                        onChange={(e) => handleFieldChange(f.param, e.target.checked ? 'true' : 'false')}
                      />
                    )}
                    {f.type === 'number' && (
                      <Box width="xsmall" direction="column" align="end">
                        <TextInput
                          size="small"
                          width="auto"
                          type="number"
                          value={f.value}
                          onChange={(e) => handleFieldChange(f.param, e.target.value)}
                        />
                        {f.param === 'm_dayToSkip' && ['DaySkipper', 'DaySkipper_Unlimited'].includes(state.target) && (
                          <Text size="xsmall" margin={{ top: '2px' }}>
                            {dateFormat === 0 && `${(((f.value/30)*31)/3600).toFixed(2)} hours`}
                            {dateFormat === 1 && `${(((f.value/30)*43)/3600).toFixed(2)} hours`}
                            {dateFormat === 2 && `${(((f.value/30)*43)/3600).toFixed(2)} hours`}
                          </Text>
                        )}
                      </Box>
                    )}
                  </Box>
                ))}
                {!state.configFields.length && <Text>Nothing to configure here - simply generate your hex!</Text>}
                <Box direction="row-reverse" gap="medium">
                  <Button
                    type="submit"
                    primary
                    hoverIndicator={false}
                    label="Generate Hex"
                    margin={{ top: '20px' }}
                  />
                </Box>
              </Form>
            </Box>
          </Box>
        </Box>
      )}
    </ResponsiveContext.Consumer>
  );
}
