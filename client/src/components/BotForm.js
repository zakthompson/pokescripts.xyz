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
  Anchor,
} from 'grommet';
import { Alert, Add, Subtract } from 'grommet-icons';

import {
  dateSkipTimings,
  fossilReviveTime,
  autoLotoTime,
  boxReleaseTime,
  boxTradeTime,
  boxTradeTimeWithPokedex,
  eggCollectTime,
  eggColumnHatchTime,
  deleteFriendTime,
  infiniteHatcherTimes,
  dupTime,
} from '../utils/constants';

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

  function addLinkCode() {
    const index = state.configFields.findIndex(
      (e) => e.param === 'm_linkCodes',
    );
    const newValue = [...state.configFields[index].value];
    newValue.push('00000000');
    handleFieldChange('m_linkCodes', newValue);
  }

  function removeLinkCode(i) {
    const index = state.configFields.findIndex(
      (e) => e.param === 'm_linkCodes',
    );
    const newValue = [...state.configFields[index].value];
    newValue.splice(i, 1);
    handleFieldChange('m_linkCodes', newValue);
  }

  return (
    <ResponsiveContext.Consumer>
      {(size) => (
        <Box
          flex
          direction="row"
          align="stretch"
          justify="stretch"
          background="gray"
          overflow={{ vertical: 'auto' }}
          pad="40px"
        >
          <Box
            direction={`${
              !['large', 'xlarge', 'xxlarge'].includes(size) ? 'column' : 'row'
            }`}
            align="start"
          >
            <Box
              direction="column"
              pad={{
                left: '20px',
                right: !['large', 'xlarge', 'xxlarge'].includes(size)
                  ? '20px'
                  : '60px',
              }}
              flex={{
                grow: 1,
                shrink: !['large', 'xlarge', 'xxlarge'].includes(size) ? 0 : 1,
              }}
            >
              <Box direction="row" flex={{ grow: 1, shrink: 0 }}>
                <Heading margin={{ top: '0px' }} level="3">
                  {state.name}
                </Heading>
              </Box>
              <Box direction="column">
                <Text size="small">{state.description}</Text>
                <Heading level="4">Instructions</Heading>
                {state.instructions.map((i, index) => (
                  <CheckBox
                    key={index}
                    size="small"
                    label={
                      <Text margin={{ vertical: '5px' }} size="small">
                        {i}
                      </Text>
                    }
                  />
                ))}
                <Heading level="4">What Will the Bot Do?</Heading>
                <ul style={{ marginTop: '0px', marginBottom: '40px' }}>
                  {state.botActions.map((i, index) => (
                    <li key={index} style={{ margin: '5px 0' }}>
                      <Text size="small">{i}</Text>
                    </li>
                  ))}
                </ul>
              </Box>
            </Box>
            <Box
              background="white"
              width={
                !['large', 'xlarge', 'xxlarge'].includes(size)
                  ? '100%'
                  : '600px'
              }
              round="small"
              flex={{ grow: 0, shrink: 0 }}
              pad="25px"
              elevation="medium"
              margin={{ bottom: '40px' }}
            >
              <Heading level="4" margin={{ top: '0px' }}>
                Configuration
              </Heading>
              <Form onSubmit={onSubmit}>
                {state.configFields.map((f) => {
                  let totalSeconds = 0;
                  let days;
                  let hours;
                  let minutes;
                  let seconds;
                  const timingStrArr = [];
                  if (
                    f.param === 'm_dayToSkip' &&
                    ['DaySkipper', 'DaySkipper_Unlimited'].includes(
                      state.target,
                    )
                  ) {
                    totalSeconds = (f.value / 30) * dateSkipTimings[dateFormat];
                  } else if (
                    state.target === 'AutoFossil' &&
                    f.param === 'm_timesBeforeSR'
                  ) {
                    totalSeconds = f.value * fossilReviveTime;
                  } else if (
                    state.target === 'AutoLoto' &&
                    f.param === 'm_dayToSkip' &&
                    f.value !== 0
                  ) {
                    totalSeconds = f.value * autoLotoTime;
                  } else if (
                    state.target === 'BoxRelease' &&
                    f.param === 'm_boxCount'
                  ) {
                    totalSeconds = f.value * boxReleaseTime;
                  } else if (
                    state.target === 'BoxSurpriseTrade' &&
                    f.param === 'm_boxesToTrade'
                  ) {
                    if (
                      state.configFields.find(
                        (f) => f.param === 'm_completeDex',
                      ).value === 'true'
                    ) {
                      totalSeconds = f.value * boxTradeTime;
                    } else {
                      totalSeconds = f.value * boxTradeTimeWithPokedex;
                    }
                  } else if (
                    state.target === 'EggCollector' &&
                    f.param === 'm_maxCycle'
                  ) {
                    totalSeconds = f.value * eggCollectTime;
                  } else if (
                    state.target === 'EggHatcher' &&
                    f.param === 'm_columnsOfEggs'
                  ) {
                    totalSeconds = f.value * eggColumnHatchTime;
                  } else if (
                    state.target === 'FriendDeleteAdd' &&
                    f.param === 'm_deleteCount'
                  ) {
                    totalSeconds = f.value * deleteFriendTime;
                  } else if (
                    state.target === 'InfiniteHatcher' &&
                    f.param === 'm_boxesToFill'
                  ) {
                    totalSeconds =
                      f.value *
                      (infiniteHatcherTimes[
                        state.configFields.find(
                          (f) => f.param === 'm_eggStepGroup',
                        ).value - 1
                      ] *
                        60);
                  } else if (
                    state.target === 'GodEggDuplication' &&
                    f.param === 'm_maxCycle'
                  ) {
                    totalSeconds = f.value * dupTime;
                  }
                  if (totalSeconds) {
                    days = Math.floor(totalSeconds / 86400);
                    hours = Math.floor((totalSeconds % 86400) / 3600);
                    minutes = Math.floor((totalSeconds % 3600) / 60);
                    seconds = Math.round(totalSeconds % 60);
                    if (days) {
                      timingStrArr.push(`${days} day${days === 1 ? '' : 's'}`);
                    }
                    if (hours) {
                      timingStrArr.push(
                        `${hours} hour${hours === 1 ? '' : 's'}`,
                      );
                    }
                    if (minutes) {
                      timingStrArr.push(
                        `${minutes} minute${minutes === 1 ? '' : 's'}`,
                      );
                    }
                    if (seconds) {
                      timingStrArr.push(
                        `${seconds} second${seconds === 1 ? '' : 's'}`,
                      );
                    }
                  }

                  return (
                    <Box
                      key={f.param}
                      direction="row"
                      align="center"
                      justify="between"
                      pad={{ vertical: '20px' }}
                      border={{ color: 'gray', size: 'small', side: 'bottom' }}
                      flex
                    >
                      <Box width="70%" direction="column" gap="small">
                        <Text>{f.name}:</Text>
                        {timingStrArr.length > 0 && (
                          <Box align="end" direction="row" gap="xsmall">
                            <Text size="xsmall" weight="bold">
                              Approx. Time:
                            </Text>
                            <Text size="xsmall" margin={{ top: '2px' }}>
                              {timingStrArr.join(', ')}
                            </Text>
                          </Box>
                        )}
                        {f.description && (
                          <Text size="small" color="darkGray">
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
                            <Text size="small" weight="bold" color="yellow">
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
                            onChange={({ option }) =>
                              handleFieldChange(f.param, option.value)
                            }
                          />
                        </Box>
                      )}
                      {f.type === 'bool' && (
                        <CheckBox
                          checked={f.value === 'true'}
                          onChange={(e) =>
                            handleFieldChange(
                              f.param,
                              e.target.checked ? 'true' : 'false',
                            )
                          }
                        />
                      )}
                      {f.type === 'number' && (
                        <Box width="xsmall" direction="column" align="end">
                          <TextInput
                            size="small"
                            width="auto"
                            type="number"
                            min={0}
                            value={f.value}
                            onChange={(e) =>
                              handleFieldChange(f.param, e.target.value)
                            }
                          />
                        </Box>
                      )}
                      {f.type === 'numberArray' && (
                        <Box width="small" direction="column" align="end">
                          {f.value.map((v, i) => {
                            const newValue = [...f.value];
                            return (
                              <Box key={i} direction="row">
                                <TextInput
                                  size="small"
                                  width="auto"
                                  type="text"
                                  value={v}
                                  onChange={(e) => {
                                    newValue[i] = e.target.value;
                                    handleFieldChange(f.param, newValue);
                                  }}
                                />
                                {f.value.length > 1 && (
                                  <Anchor
                                    icon={<Subtract />}
                                    onClick={() => removeLinkCode(i)}
                                    hoverIndicator
                                  />
                                )}
                              </Box>
                            );
                          })}
                          <Anchor
                            icon={<Add />}
                            onClick={addLinkCode}
                            hoverIndicator
                          />
                        </Box>
                      )}
                    </Box>
                  );
                })}
                {!state.configFields.length && (
                  <Text>
                    Nothing to configure here - simply generate your hex!
                  </Text>
                )}
                <Box
                  direction="row"
                  justify={
                    [
                      'Auto3DaySkipper',
                      'AutoLoto',
                      'BerryFarmer',
                      'WattFarmer',
                    ].includes(state.target)
                      ? 'between'
                      : 'end'
                  }
                  align="center"
                  gap="medium"
                  margin={{ top: '20px' }}
                >
                  {state.target === 'Auto3DaySkipper' && (
                    <Box direction="row" align="center">
                      <Text
                        size="small"
                        weight="bold"
                        margin={{ right: '5px' }}
                      >
                        Approx. Time per Loop:
                      </Text>
                      <Text size="small">1 minute, 40 seconds</Text>
                    </Box>
                  )}
                  {state.target === 'AutoLoto' && (
                    <Box direction="row" align="center">
                      <Text
                        size="small"
                        weight="bold"
                        margin={{ right: '5px' }}
                      >
                        Approx. Time per Loto:
                      </Text>
                      <Text size="small">20 seconds</Text>
                    </Box>
                  )}
                  {state.target === 'BerryFarmer' && (
                    <Box direction="row" align="center">
                      <Text
                        size="small"
                        weight="bold"
                        margin={{ right: '5px' }}
                      >
                        Approx. Time per Gather:
                      </Text>
                      <Text size="small">15 seconds</Text>
                    </Box>
                  )}
                  {state.target === 'WattFarmer' && (
                    <Box direction="row" align="center">
                      <Text
                        size="small"
                        weight="bold"
                        margin={{ right: '5px' }}
                      >
                        Approx. Time per Collect:
                      </Text>
                      <Text size="small">8 seconds</Text>
                    </Box>
                  )}
                  <Button
                    type="submit"
                    primary
                    hoverIndicator={false}
                    label="Generate Hex"
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
