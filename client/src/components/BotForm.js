import React from 'react';
import {
  Box,
  Button,
  CheckBox,
  Form,
  Heading,
  Select,
  Text,
  TextInput,
} from 'grommet';
import { Alert } from 'grommet-icons';

export default function BotForm({ state, setState, onSubmit }) {
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
    <Box
      flex
      align="center"
      justify="start"
      background="gray"
      overflow={{ vertical: 'auto' }}
      pad="20px"
    >
      <Box
        align="stretch"
        width="large"
        background="white"
        round="small"
        pad="20px"
        flex={{ shrink: 0 }}
      >
        <Heading level="3">{state.name}</Heading>
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
              <Box width="60%" direction="column" gap="small">
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
                <Select
                  size="small"
                  options={f.options}
                  value={f.options.find((o) => o.value === f.value)}
                  labelKey="name"
                  onChange={({ option }) => handleFieldChange(f.param, option.value)}
                />
              )}
              {f.type === 'bool' && (
                <CheckBox
                  checked={f.value === 'true'}
                  onChange={(e) => handleFieldChange(f.param, e.target.checked ? 'true' : 'false')}
                />
              )}
              {f.type === 'number' && (
                <Box width="small">
                  <TextInput
                    size="small"
                    width="auto"
                    type="number"
                    value={f.value}
                    onChange={(e) => handleFieldChange(f.param, e.target.value)}
                  />
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
  );
}
