export const botConfigs = [
  {
    name: 'Auto Roller',
    target: 'AutoRoller',
    description:
      'This bot skips frames forward to a random Pokemon in a wishing piece den and repeats - useful for rolling a particular Pokemon on your shiny frame. By default, it skips 3 frames at a time, but this can be changed to any number you like. Set it to 0 to skip forever.',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that your system time is unsynced',
      'Face the wishing piece den, with Watts collected, on your bike. Save in this position',
      'Ensure that your volume is up',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'First, the bot will sync and unsync the system time to reset to current date',
      'It will then use the invite glitch to skip the desired frames forward',
      'If set to 0, it will continue this loop forever',
      'Otherwise, after skipping it will ring the bike bell several times to get your attention on your shiny frame before checking the den',
      'If left alone, the bot will restart the game and continue the loop - unplug the bot if you see the Pokemon you want!',
      "The bot will sync and unsync date every 20 skips to ensure it doesn't hit the max year",
    ],
    configFields: [
      {
        param: 'm_daysToSkip',
        name: 'Days to Skip',
        description: 'Set to 0 to skip forever',
        type: 'number',
        value: 3,
      },
      {
        param: 'm_titleScreenBuffer',
        name: 'Wait Longer at Title Screen',
        description:
          "Older or hacked Switches sometimes take longer loading the title screen. You'll know this is happening if the title screen plays for a long time before entering the game. If this happens to you, check this box, and the bot will wait a little longer before pressing A to skip the title screen.",
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Auto Fossil Restore',
    target: 'AutoFossil',
    description:
      'This bot automatically speaks to Cara Liss to revive fossils - perfect for hunting shiny fossil Pokemon!',
    instructions: [
      'Ensure that your text speed is set to "Fast" and nicknames are set to "Don\'t Give"',
      'Save in front of Cara Liss on Route 6',
      'Ensure that the fossil you are reviving is registered in your Pokedex',
      'Confirm which slot the two fossils you want to choose are - top or bottom - and configure this hex accordingly',
      "Ensure that you have enough of both fossils in your inventory to revive the number you've configured",
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will continue reviving fossils until it hits the number configured here',
      'If "Restart After Revives" is not set, the bot will go to the Home menu when finished',
      "If it is set, you'll want to monitor each revive to see if you get a shiny - the bot will restart automatically once the number is hit",
    ],
    configFields: [
      {
        param: 'm_firstFossilTopSlot',
        name: 'First Fossil Slot',
        type: 'select',
        options: [
          { name: 'Top', value: 'true' },
          { name: 'Bottom', value: 'false' },
        ],
        value: 'true',
      },
      {
        param: 'm_secondFossilTopSlot',
        name: 'Second Fossil Slot',
        type: 'select',
        options: [
          { name: 'Top', value: 'true' },
          { name: 'Bottom', value: 'false' },
        ],
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
        name: 'Revives Before End/Restart',
        type: 'number',
        value: 150,
      },
    ],
  },
  {
    name: 'Auto Host',
    target: 'AutoHost',
    description:
      'This bot will automatically host raids for as long as you keep it running. There are lots of configuration options available based on your preferences!',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Stand in front of your wishing piece den with Watts collected and save',
      'Ensure that you are offline',
      'If rolling new Pokemon between raids, ensure that your system time is unsynced - and save 3 frames before your shiny frame',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'If rolling between raids, the bot will first roll your first Pokemon - if not, ignore this step',
      'The bot will connect to the Internet via Y-Comm',
      'It will then open the den, set a link code (if configured to do so) and invite others',
      'If desired, it will navigate to your profile and add friends while waiting for people to join (about 9 requests if waiting until 2-minute mark, 18 if waiting until 1-minute mark)',
      'After the wait time is reached, it will begin the raid and disconnect, either by closing the game or cutting the Internet connection, to return you to outside of the den',
      'Each raid takes between 2:15 and 2:45 depending on configuration',
    ],
    configFields: [
      {
        param: 'm_internetTime',
        name: 'Time to Connect to Internet',
        description:
          'Adjust this to be higher if your connection is slow, or lower if your connection is fast',
        type: 'number',
        value: 900,
      },
      {
        param: 'm_skip3Days',
        name: 'Roll New Pokemon Each Raid',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_unsafeDC',
        name: 'Use Unsafe DC',
        description:
          'Will disconnect from raid using the "Search for Local Friends" method, which means you don\'t need to save-lock to a Pokemon.',
        warning:
          'If a raid fires with nobody in it, disconnecting will not work, and the bot will break!',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_useLinkCode',
        name: 'Use Link Codes',
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
        param: 'm_linkCodes',
        name: 'Link Codes',
        type: 'numberArray',
        value: ['69696969'],
      },
      {
        param: 'm_waitTime',
        name: 'When to Fire Raid',
        type: 'select',
        options: [
          { name: '2-Minute Mark', value: 0 },
          { name: '1-Minute Mark', value: 1 },
        ],
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
        description:
          'If your Switch has multiple profiles on it, set this to the number (from left to right) that should be used.',
        type: 'number',
        value: 1,
      },
      {
        param: 'm_alternate',
        name: 'Alternate FFA and Coded',
        description:
          'When selected, each raid will flip between free-for-all and coded. This makes the "Use Link Code" option only determine what the first raid in the sequence will be.',
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_titleScreenBuffer',
        name: 'Wait Longer at Title Screen',
        description:
          "Older or hacked Switches sometimes take longer loading the title screen. You'll know this is happening if the title screen plays for a long time before entering the game. If this happens to you, check this box, and the bot will wait a little longer before pressing A to skip the title screen.",
        type: 'bool',
        value: 'false',
      },
      {
        param: 'm_localMode',
        name: 'Local Hosting Mode',
        description:
          'Skips connecting to the Internet for hosting local-only raids.',
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Auto Loto',
    target: 'AutoLoto',
    description:
      "This bot grinds the Rotom Loto for rewards. It's recommended that you have several boxes of Pokemon with different trainer IDs to maximize your chances of winning.",
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that your system time is unsynced',
      'Stand in front of a Rotom PC',
      'Activate the Y-Comm glitch',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'First, the bot will sync and unsync the system time to reset to current date',
      'Next, it will skip one frame forward',
      'Then it will check the Rotom Loto and collect reward, and repeat from step 1',
      'If a maxmimum number of tries is specified, it will finish on the Home menu. Otherwise, it will continue forever',
    ],
    configFields: [
      {
        param: 'm_dayToSkip',
        name: 'Maximum Attempts',
        description:
          'You can optionally set a maximum number of attempts. Set it to 0 for no limit.',
        type: 'number',
        value: 0,
      },
    ],
  },
  {
    name: 'Berry Farmer',
    target: 'BerryFarmer',
    description:
      'This bot will farm berries from a single tree - great for collecting berries that reset EVs, increase happiness, or are used for competitive play. Also great for collecting Leftovers!',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that your system time is unsynced',
      "Stand in front of the berry tree you want to farm (make sure it's far from any wandering Pokemon!)",
      'Activate Y-Comm glitch',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'First, the bot will sync and unsync the system time to reset to current date',
      'Next, it will skip one frame forward',
      'Then it will shake the berry tree only once',
      'It will save after the number of attempts specified here',
    ],
    configFields: [
      {
        param: 'm_saveAt',
        name: 'Save After Attempts',
        description:
          'To prevent loss of berries if the game crashes, set a number of times you would like to collect before saving.',
        type: 'number',
        value: 50,
      },
    ],
  },
  {
    name: 'Box Release',
    target: 'BoxRelease',
    description:
      'This bot releases all Pokemon in one or multiple boxes. Useful for getting rid of your breeding rejects!',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Make sure all the boxes you want to release are side-by-side, with no eggs or empty spaces in-between',
      'Your final box does not need to be full, but must have Pokemon arranged from left to right, top to bottom',
      'Ensure your cursor is on "Select" mode and move it to the first box\'s top-left slot',
      'Plug in the bot to start the loop',
    ],
    botActions: [
      'The bot will release the Pokemon in the boxes from left to right, top to bottom',
      "Once finished, it will return to the Home menu to signal that it's finished",
    ],
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
    description:
      'This bot automatically surprise trades entire boxes of Pokemon. Useful for stocking up on different trainer IDs for the Rotom Loto!',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that you are not in the Wild Area (to avoid lag)',
      "Make sure that all your trade boxes are side-by-side, with no eggs or empty spaces in-between (empty spaces won't actually break it, just wastes time)",
      'Ensure that the first box you want to trade is active (the game remembers the last box you had open)',
      'Connect to the Internet in your Y-Comm',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will surprise trade each Pokemon in your selected boxes from left to right, top to bottom',
      'Note that a trade may fail if a partner is not found in 30 seconds, if the received Pokemon has a trade evolution, or if a new Pokedex entry is received without the bot being configured to handle it',
      'Usually this will just cause the bot to miss one trade, but if it happens on the last Pokemon in a box, the bot may fail to move onto the next box',
      "To avoid this, it's recommended to monitor near the end of each box",
    ],
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
        description:
          "Set this only if you have completed your Pokedex. If you haven't, the bot will leave extra time for any new Pokedex entries you may receive.",
        type: 'bool',
        value: 'true',
      },
    ],
  },
  {
    name: 'Day Skipper',
    target: 'DaySkipper',
    description:
      "This bot advances frames automatically - useful for skipping to your shiny frame! Note that there are two versions of this bot. This one fully advances your date, making it easier to tell how close you are to finished - however, it has a limit of 22,280 days, since the Switch's max date is December 31st, 2060. If your skip would take you beyond that, check out Day Skipper (Unlimited) instead!",
    instructions: [
      'Ensure that your system time is unsynced',
      'If you are not using JP date format, make sure that your system time is NOT between 1am and 3am (certain date/time combinations will be invalid due to Daylight Savings Time)',
      'Go to a Pokemon Center to avoid crashing your game',
      'Activate the Y-Comm glitch',
      'Plug in the bot with your cursor over the date selector in the Date and Time Menu',
    ],
    botActions: [
      'The bot will skip days, months and years correctly',
      'Once finished, it will return to the game',
    ],
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
        warning:
          'This day skipper has a maximum of 22,280 days. If you need to skip more than that, use the "unlimited" version.',
        type: 'number',
        value: 1000,
      },
    ],
  },
  {
    name: 'Day Skipper (Unlimited)',
    target: 'DaySkipper_Unlimited',
    description:
      "This bot advances frames automatically - useful for skipping to your shiny frame! Note that there are two versions of this bot. This one has no limit because it only ever advances the day - it knows not to count going from 31 -> 1 as a skip. The disadvantage is that you have no way of knowing its progress - if your skip is less than 22,280 frames, and you'd like to be able to monitor progress, use the regular Day Skipper instead.",
    instructions: [
      'Ensure that your system time is unsynced and set to the first day of any month with 31 days',
      'Go to a Pokemon Center to avoid crashing your game',
      'Activate the Y-Comm glitch',
      'Plug in the bot with your cursor over the date selector in the Date and Time Menu',
    ],
    botActions: [
      'The bot will skip only days, knowing not to count the change from 31 -> 1',
      'Once finished, it will return to the game',
    ],
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
    description:
      "This bot automatically collects eggs from the Route 5 nursery. It makes use of the Rotom bike's turbo boost to be as efficient as possible. Note that the number you configure is how many times the bot will attempt to get an egg, but not every attempt will be successful. If you have the Oval Charm and both Pokemon in the daycare have different trainer IDs, you should receive approximately 80% of your target.",
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that "Send to Boxes" is set to "Automatic"',
      'Your Rotom bike must be fully upgraded',
      'Your party must be full of Pokemon, no eggs',
      'Go to the Route 5 nursery and charge up your Rotom bike boost',
      'Cycle up to the left side of the nursery worker',
      'Plug in the bot to start the loop',
    ],
    botActions: [
      'The bot does a turbo boosted loop, then attempts to collect an egg',
      'Once all attempts have been completed, it will go to the Home menu',
    ],
    configFields: [
      {
        param: 'm_maxCycle',
        name: 'Attempts to Collect',
        description:
          "The bot will make this many attempts to collect an egg. You can set this to 0 to run it indefinitely, but running out of box space is untested, so it's recommended you monitor it.",
        type: 'number',
        value: 90,
      },
    ],
  },
  {
    name: 'Egg Hatcher',
    target: 'EggHatcher',
    description:
      'This bot hatches columns of eggs from your boxes using the Rotom bike turbo boost for efficiency.',
    instructions: [
      'Ensure that your text speed is set to "Fast" and nicknames are set to "Don\'t Give"',
      'Have only one Pokemon in your party, and that Pokemon must have the Flame Body ability',
      'Make sure that the Pokemon you are hatching is already registered in your Pokedex',
      'Make sure your Rotom bike is fully upgraded',
      'Go to the Route 5 nursery and charge up your Rotom bike boost',
      'Cycle down and to the right until you hit the first NPC on the bridge',
      'Ensure that all of your columns of eggs are adjacent to each other in your boxes',
      'All columns must have 5 eggs except the final one, or the bot will break',
      'If doing multiple species of Pokemon, they must all take the same number of steps to hatch',
      'Move the cursor to the top of the leftmost column of eggs and set your cursor to "Multiselect"',
      'Plug the bot in to begin the loop',
    ],
    botActions: [
      'The bot will pick up 5 eggs and do loops until all 5 eggs hatch',
      'It will then return to the starting point, put the hatched Pokemon back into your box, and pick up the next column to start again',
      'Once finished, it will bring you to the Home menu',
    ],
    configFields: [
      {
        param: 'm_eggStepGroup',
        name: 'Egg Group Steps',
        description:
          "Use Serebii or Bulbapedia to figure out how many steps your Pokemon's Egg Group takes to hatch.",
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
        value: 3,
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
    name: 'Infinite Egg Hatcher (BETA)',
    target: 'InfiniteHatcher',
    description: `This bot is significantly slower than the the Collector/Hatcher combo, but does not require two separate steps. It will continually collect eggs from the Bridge Field nursery and hatch them, filling boxes up to a specified maximum. Note that, similar to the Egg Collector bot, it is possible that an egg will not be collected every time, so some spots in your boxes may be skipped. For the best results, be sure to have the Oval Charm and have Pokemon with different trainer IDs in the nursery. Unfortunately, this bot only works with Pokemon who take 2560 steps or higher to hatch. Additionally, if you are doing a 2560-step Pokemon, only 3 eggs will be collected each cycle, meaning 12 slots will be empty each box.`,
    instructions: [
      'Ensure that your text speed is set to "Fast" and nicknames are set to "Don\'t Give"',
      'Have only one Pokemon in your party, and that Pokemon must have the Flame Body ability',
      'Make sure that the Pokemon you are hatching is already registered in your Pokedex',
      'Go to Bridge Field and get on your bike',
      'Ensure that you are not conneced to the Internet',
      'Your Pokemon icon in the game menu MUST be in the top row, second column',
      'Your Town Map icon in the game menu MUST be in the second row, first column',
      'Ensure that all your empty boxes are adjacent, and that your cursor is over the top-left slot in the first empty box (the game remembers its position)',
      'Ensure that your menu cursor is over Town Map (the game remembers its position)',
      'An egg should be ready to pick up at the nursery (not strictly necessary, but you will have an empty slot otherwise)',
      'Plug the bot in to begin the loop',
    ],
    botActions: [
      'The bot will open the Town Map and taxi to Bridge Field to reset position',
      'It will then continuously pick up eggs, hatch them, and drop them off in your boxes',
      'Once the set number of boxes has been filled, it will stop',
    ],
    configFields: [
      {
        param: 'm_eggStepGroup',
        name: 'Egg Group Steps',
        description:
          "Use Serebii or Bulbapedia to figure out how many steps your Pokemon's Egg Group takes to hatch.",
        type: 'select',
        options: [
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
        value: 3,
      },
      {
        param: 'm_boxesToFill',
        name: 'Boxes to Fill',
        type: 'number',
        value: 3,
      },
    ],
  },
  {
    name: 'God Egg Duplication',
    target: 'GodEggDuplication',
    description:
      "This bot automatically duplicates Pokemon using the God Egg exploit. It makes use of the Rotom bike's turbo boost to be as efficient as possible. Note that the number you configure is how many times the bot will attempt to duplicate, but not every attempt will be successful. If you have the Oval Charm and both Pokemon in the daycare have different trainer IDs, you should receive approximately 80% of your target. Actually acquiring the God Egg is up to you.",
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that "Send to Boxes" is set to "Manual"',
      'Your Rotom bike must be fully upgraded',
      'Your party must be full of Pokemon, no eggs',
      'The first Pokemon in your party must be the one you want to duplicate',
      'Go to the Route 5 nursery, deposit God Egg and a Ditto, and charge up your Rotom bike boost',
      'Cycle up to the left side of the nursery worker',
      'Plug in the bot to start the loop',
    ],
    botActions: [
      'The bot does a turbo boosted loop, then attempts to collect an egg',
      'If an egg is collected, it will try to swap it with the first Pokemon in your party, thus duplicating that Pokemon',
      'Once all attempts have been completed, it will go to the Home menu',
    ],
    configFields: [
      {
        param: 'm_maxCycle',
        name: 'Attempts to Duplicate',
        description:
          "The bot will make this many attempts to duplicate a Pokemon. You can set this to 0 to run it indefinitely, but running out of box space is untested, so it's recommended you monitor it.",
        type: 'number',
        value: 30,
      },
    ],
  },
  {
    name: 'Delete Friends',
    target: 'FriendDeleteAdd',
    description:
      "This bot will delete the specified number of friends, and optionally add friends afterward. Note that it will also delete best friends if you aren't careful about how you use it!",
    instructions: [
      'In your friend list, hover your cursor over the first friend you wish to delete',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will delete friends until the specified number has been reached',
      'If configured to do so, it will then go to your friend requests and press A forever to accept them all',
    ],
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
        description:
          'If enabled, the bot will accept friend-requests after deleting friends.',
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Turbo A',
    target: 'TurboA',
    description:
      'This bot just spams the A button forever. It is mostly useful for farming items from the Digging Duo - and maybe getting through conversations with Hop.',
    instructions: [
      'Stand in front of the desired Digging Duo brother',
      'Plug in the bot to begin the loop',
    ],
    botActions: ['It spams the A button. Forever.'],
    configFields: [],
  },
  {
    name: 'Watt Farmer',
    target: 'WattFarmer',
    description: 'This bot farms Watts from a wishing piece den.',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that your system time is unsynced',
      'Stand in front of a wishing piece den',
      'Activate Y-Comm glitch',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'First, the bot will sync and unsync system time to reset to current date',
      'It will then skip one frame forward, collect Watts from the den, and exit',
      'After the configured number of collections, it will save the game to avoid loss of Watts if the game crashes',
    ],
    configFields: [
      {
        param: 'm_saveAt',
        name: 'Save After',
        description:
          'To avoid losing progress due to a crash, the bot will save after a specified number of Watt collections.',
        type: 'number',
        value: 50,
      },
    ],
  },
  {
    name: 'Purple Beam Hunter',
    target: 'PurpleBeam',
    description:
      "This bot will repeatedly throw Wishing Pieces into an empty den, then exit out into the Home menu before saving can complete. You'll need to watch to see what kind of beam shows up, but hey, at least you don't have to use your hands.",
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure that you are on your bike in front of an empty den',
      'Ensure that the den has no Watts to collect',
      'Ensure that you have at least 1 Wishing Piece',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'First, the bot will ring the bike bell to get your attention',
      'It will then throw in a Wishing Piece and exit to Home before saving completes',
      'If left for a few seconds, it will restart the game and begin the loop again',
      "If you don't see red streaks coming from the den before going to the home menu, you found a purple beam. Simply unplug the bot to stop the loop",
      "Note that you won't see the purple beam itself since the bot enters the home menu before it is shown in the game",
    ],
    configFields: [
      {
        param: 'm_titleScreenBuffer',
        name: 'Wait Longer at Title Screen',
        description:
          "Older or hacked Switches sometimes take longer loading the title screen. You'll know this is happening if the title screen plays for a long time before entering the game. If this happens to you, check this box, and the bot will wait a little longer before pressing A to skip the title screen.",
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Auto Tournament',
    target: 'AutoTournament',
    description:
      'This bot will repeatedly beat the championship tournament - useful for grinding apriballs and orbs.',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Set Battle Effects to "Off"',
      'Have a Zacian in front of your party with the following stats:',
      'Level: 100',
      'Held Item: Rusted Sword',
      'Ability: Intrepid Sword',
      'EVs: 252 Atk, Optional: 4 Def, 252 Spe',
      'Nature: Adamant',
      'First move: Iron Head (PP Maxed)',
      'Stand in front of the Wyndon Stadium receptionist',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will loop battling through the championship tournament forever',
      'If you win, it will collect your reward from the Ball Guy',
      'If you lose, it will eventually rejoin',
    ],
    configFields: [],
  },
  {
    name: 'Auto Battle Tower',
    target: 'AutoBattleTower',
    description:
      'This bot will repeatedly fight in the Battle Tower in Wyndon - great for grinding BP for those mints and ability capsules!',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Set Battle Effects to "Off"',
      'Go to VS -> Battle Stadium -> Rental Teams and rent the team with ID 0000-0006-15Y4-3R',
      'Join Single Battle on Battle Tower, choose the team above and have Zacian in the front',
      'Play until you can press Fight on the first battle',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will loop fighting the Battle Tower forever',
      'It is able to switch Pokemon and re-enter on loss, pause or win',
    ],
    configFields: [],
  },
  {
    name: 'Shiny Hunt Regi (NEW!)',
    target: 'ShinyFiveRegi',
    description:
      'This bot will repeat the encounter with any of the Regi Pokemon, lighting up the necessary tiles automatically.',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Ensure your first Pokemon is either fast enough to run away from the battle, or holding a Smoke Bomb to guarantee escape',
      'For Regirock, Regice or Registeel: Walk up to the giant statue without lighting any tiles',
      'For Regieleki or Regidrago: First, light up the appropriate tiles, select the Regi you want, start a battle with it and run',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will run on the appropriate tiles for the Regi you are hunting, then walk up to the statue to start the encounter',
      'You will have to look at your Switch to see if the Pokemon is shiny - if it is, unplug the bot',
      "If it's not, leave it alone and the bot will run from the battle and start over",
    ],
    configFields: [
      {
        param: 'm_type',
        name: 'Regi to Hunt',
        type: 'select',
        options: [
          {
            name: 'Regirock',
            value: 0,
          },
          {
            name: 'Regice',
            value: 1,
          },
          {
            name: 'Registeel',
            value: 2,
          },
          {
            name: 'Regieleki',
            value: 3,
          },
          {
            name: 'Regidrago',
            value: 4,
          },
        ],
        value: 0,
      },
      {
        param: 'm_fastMode',
        name: 'Fast Mode',
        description:
          'If your lead Pokemon is NOT shiny, does NOT have an ability that pops up on screen (such as Unnerve), and does NOT have high happiness (which can trigger extra animations at the start of battle), turning this on will run from battle quicker.',
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Shiny Hunt Sword Trio (NEW!)',
    target: 'ShinySwordTrio',
    description:
      'This bot will automatically loop an encounter with a Sword Trio Pokemon.',
    instructions: [
      'Ensure that your text speed is set to "Fast"',
      'Set Battle Effects to "Off"',
      'Ensure your first Pokemon is either fast enough to run away from the battle, or holding a Smoke Bomb to guarantee escape',
      'Encounter the Trio Pokemon you wish to hunt - try to remember the exact location that it spawned',
      'Run from the encounter',
      'Position your character exactly where the Pokemon spawned',
      'Start camping',
      'Plug in the bot to begin the loop',
    ],
    botActions: [
      'The bot will leave the camp, which should cause the Pokemon to spawn directly on your position',
      'You will have to look at your Switch to see if the Pokemon is shiny - if it is, unplug the bot',
      "If it's not, leave it alone and the bot will run from the battle, re-open your camp, and start over",
    ],
    configFields: [
      {
        param: 'm_fastMode',
        name: 'Fast Mode',
        description:
          "This will loop faster, but the following requirements MUST be met: Your first Pokemon must NOT be shiny and must NOT have an ability that pops up on screen (such as Unnerve). NONE of the Pokemon in your party can have high happiness (if any do, it's possible to get an extra animation while camping, which will mess up the timing). The weather MUST be clear (otherwise an extra dialogue box appears at the beginning of battle - you can change your Switch date to fix the weather if needed).",
        type: 'bool',
        value: 'false',
      },
    ],
  },
  {
    name: 'Home Releaser (NEW!)',
    target: 'HomeReleaser',
    description:
      'This bot will release Pokemon from 3 boxes in Pokemon Home. Works for both in-game boxes and Home boxes. This is much faster than releasing in game.',
    instructions: [
      'Remove all wanted Pokemon from 3 consecutive boxes.',
      'Ensure there is a Pokemon at the top left corner of each box. There can be empty spots in other places in the box, just not the first slot.',
      'Plug in the bot to mass release quickly.',
    ],
    botActions: [
      'The bot will select all Pokemon in the box and release them.',
      'It will move to the next box and repeat until it releases 3 boxes (because of the release limit).',
      'The bot then saves and exits.',
      'If you wish to release more, just enter the box again and re-plug the bot in.',
      'If you messed up somewhere, just plug the bot out and exit without saving changes before it\'s too late!'
    ],
    configFields: [],
  },
];

export const dateFormatOptions = [
  { name: 'JP', value: 0 },
  { name: 'EU', value: 1 },
  { name: 'US', value: 2 },
];

export const mcuOptions = [
  { name: 'atmega16u2 (UNO R3)', value: 'atmega16u2' },
  { name: 'at90usb1286 (Teensy 2.0++)', value: 'at90usb1286' },
  { name: 'atmega32u4 (Arduino Micro/Teensy 2.0)', value: 'atmega32u4' },
];

export const dateSkipTimings = {
  0: 17.04,
  1: 21.84,
  2: 21.84,
};
export const fossilReviveTime = 18.468;
export const autoLotoTime = 21.204;
export const berryCollectionTime = 15.56;
export const boxReleaseTime = 93.81;
export const boxTradeTime = 1962.117;
export const boxTradeTimeWithPokedex = 2070.627;
export const eggCollectTime = 16.333;
export const eggColumnHatchTime = 188.167;
export const deleteFriendTime = 10.244;
export const infiniteHatcherTimes = [18, 28, 30, 32, 33, 35, 37];
export const dupTime = 23.023;
