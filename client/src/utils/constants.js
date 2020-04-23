export const botConfigs = [
  {
    name: 'Auto 3-Day Skipper',
    target: 'Auto3DaySkipper',
    configFields: [],
  },
  {
    name: 'Auto Fossil Restore',
    target: 'AutoFossil',
    configFields: [
      {
        param: 'm_firstFossilTopSlot',
        name: 'First Fossil Slot',
        type: 'select',
        options: [{ name: 'Top', value: 'true' }, { name: 'Bottom', value: 'false' }],
        value: 'true',
      },
      {
        param: 'm_secondFossilTopSlot',
        name: 'Second Fossil Slot',
        type: 'select',
        options: [{ name: 'Top', value: 'true' }, { name: 'Bottom', value: 'false' }],
        value: 'true',
      },
      {
        param: 'm_autoSoftReset',
        name: 'Restart After Revives',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_timesBeforeSR',
        name: 'Revives Before Restart',
        type: 'number',
        value: 150,
      },
    ],
  },
  {
    name: 'Auto Host',
    target: 'AutoHost',
    configFields: [
      {
        param: 'm_internetTime',
        name: 'Time to Connect to Internet',
        type: 'number',
        value: 900,
      },
      {
        param: 'm_skip3Days',
        name: 'Roll Between Raids',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_unsafeDC',
        name: 'Use Unsafe DC',
        description: 'Will disconnect from raid using the "Search for Local Friends" method, which means you don\'t need to save-lock to a Pokemon.',
        warning: 'If a raid fires with nobody in it, disconnecting will not work, and the bot will break!',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_useLinkCode',
        name: 'Use Link Code',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_useRandomCode',
        name: 'Use Random Code',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_seed',
        name: 'Seed for Random Codes',
        type: 'number',
        value: 79,
      },
      {
        param: 'm_linkCode',
        name: 'Link Code',
        type: 'number',
        value: 6969,
      },
      {
        param: 'm_waitTime',
        name: 'When to Fire Raid',
        type: 'select',
        options: [{ name: '2-Minute Mark', value: 0 }, { name: '1-Minute Mark', value: 1 }],
        value: 0,
      },
      {
        param: 'm_addFriends',
        name: 'Add Friends Between Raids',
        type: 'bool',
        value: 'true',
      },
      {
        param: 'm_profile',
        name: 'Switch Profile',
        description: 'If your Switch has multiple profiles on it, set this to the number (from left to right) that should be used.',
        type: 'number',
        value: 1,
      },
      {
        param: 'm_alternate',
        name: 'Alternate FFA and Coded',
        description: 'When selected, each raid will flip between free-for-all and coded. This makes the "Use Link Code" option only determine what the first raid in the sequence will be.',
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Auto Loto',
    target: 'AutoLoto',
    configFields: [
      {
        param: 'm_dayToSkip',
        name: 'Max Days to Skip',
        description: 'You can optionally set a maximum number of attempts. Set it to 0 for no limit.',
        type: 'number',
        value: 0,
      },
    ],
  },
  {
    name: 'Berry Farmer',
    target: 'BerryFarmer',
    configFields: [
      {
        param: 'm_saveAt',
        name: 'Save After Attempts',
        description: 'To prevent loss of berries if the game crashes, set a number of times you would like to collect before saving.',
        type: 'number',
        value: 50,
      },
    ],
  },
  {
    name: 'Box Release',
    target: 'BoxRelease',
    configFields: [
      {
        param: 'm_boxCount',
        name: 'Boxes to Release',
        type: 'number',
        value: 2,
      },
    ],
  },
  {
    name: 'Box Surprise Trade',
    target: 'BoxSurpriseTrade',
    configFields: [
      {
        param: 'm_boxesToTrade',
        name: 'Boxes to Trade',
        type: 'number',
        value: 3,
      },
      {
        param: 'm_completeDex',
        name: 'Completed Pokedex',
        description: 'Set this only if you have completed your Pokedex. If you haven\'t, the bot will leave extra time for any new Pokedex entries you may receive.',
        type: 'bool',
        value: 'true',
      },
    ],
  },
  {
    name: 'Day Skipper',
    target: 'DaySkipper',
    configFields: [
      {
        param: 'm_day',
        name: 'Current Switch Day',
        type: 'number',
        value: 1,
      },
      {
        param: 'm_month',
        name: 'Current Switch Month',
        type: 'number',
        value: 1,
      },
      {
        param: 'm_year',
        name: 'Current Switch Year',
        type: 'number',
        value: 2020,
      },
      {
        param: 'm_dayToSkip',
        name: 'Number of Days to Skip',
        warning: 'This day skipper has a maximum of 22,280 days. If you need to skip more than that, use the "unlimited" version.',
        type: 'number',
        value: 1000,
      },
    ],
  },
  {
    name: 'Day Skipper (Unlimited)',
    target: 'DaySkipper_Unlimited',
    configFields: [
      {
        param: 'm_dayToSkip',
        name: 'Number of Days to Skip',
        type: 'number',
        value: 10000,
      },
    ],
  },
  {
    name: 'Egg Collector',
    target: 'EggCollector',
    configFields: [
      {
        param: 'm_maxCycle',
        name: 'Attempts to Collect',
        description: 'The bot will make this many attempts to collect an egg. If you have the Oval Charm and the Pokemon in the daycare have different trainer IDs, you will get about 80% of this number on average.',
        type: 'number',
        value: 90,
      },
    ],
  },
  {
    name: 'Egg Hatcher',
    target: 'EggHatcher',
    configFields: [
      {
        param: 'm_eggStepGroup',
        name: 'Egg Group Steps',
        description: 'Use Serebii or Bulbapedia to figure out how many steps your Pokemon\'s Egg Group takes to hatch.',
        type: 'select',
        options: [
          {
            name: '1280 Steps',
            value: 0,
          },
          {
            name: '2560 Steps',
            value: 1,
          },
          {
            name: '3840 Steps',
            value: 2,
          },
          {
            name: '5120 Steps',
            value: 3,
          },
          {
            name: '6400 Steps',
            value: 4,
          },
          {
            name: '7680 Steps',
            value: 5,
          },
          {
            name: '8960 Steps',
            value: 6,
          },
          {
            name: '10240 Steps',
            value: 7,
          },
        ],
        value: 0,
      },
      {
        param: 'm_columnsOfEggs',
        name: 'Columns of Eggs',
        type: 'number',
        value: 6,
      },
    ],
  },
  {
    name: 'Delete Friends',
    target: 'FriendDeleteAdd',
    configFields: [
      {
        param: 'm_deleteCount',
        name: 'Number to Delete',
        type: 'number',
        value: 4,
      },
      {
        param: 'm_addFriend',
        name: 'Add Friends',
        description: 'If enabled, the bot will accept friend-requests after deleting friends.',
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Turbo A',
    target: 'TurboA',
    configFields: [],
  },
  {
    name: 'Watt Farmer',
    target: 'WattFarmer',
    configFields: [
      {
        param: 'm_saveAt',
        name: 'Save After',
        description: 'To avoid losing progress due to a crash, the bot will save after a specified number of Watt collections.',
        type: 'number',
        value: 50,
      },
    ],
  },
];

export const dateFormatOptions = [
  { name: 'JP', value: 0 },
  { name: 'EU', value: 1 },
  { name: 'US', value: 2 },
];
