# Instructions

1. Ensure that your text speed is set to "Fast" and nicknames is set to "Don't Give"
2. Have only one Pokemon in your party, and that Pokemon should have the Flame Body ability
3. The Pokemon you are hatching must already be registered in your Pokedex (if it isn't, simply hatch one egg manually)
4. Set your bike to high gear.
5. Go to the corner of the fence right outside the nursery.
6. Make sure your Pokétch is on your screen and set to the Pedometer (step tracker) and your cursor when you Press R is over the clear button.
   - This is optional to let you know how far in each egg hatching cycle you are at currently. If you don't wish to keep track, just make sure when you open the Poketch and press A, nothing pops up like the Fly menu or some dialog
7. Ensure that your eggs are arranged in _full columns_ with _no gaps_ in between (the last column can have less than 5 in it)
8. Move the cursor to the top egg in the left column and set your cursor to multiselect
9. Plug in the bot to start the loop

**Note:** The bot will go to your Switch's home menu when finished

## Configuration Options

### m_eggStepGroup

This determines how long the bot will need to bike before the eggs hatch. You'll need to find out how many steps it takes your desired Pokemon to hatch either from Serebii or Bulbapedia, then set this config value to the appropriate number below:

0 = 1280 steps
1 = 2560 steps
2 = 3840 steps
3 = 5120 steps
4 = 6400 steps
5 = 7680 steps
6 = 8960 steps
7 = 10240 steps

### m_columnsOfEggs

The number of _columns_ of eggs you want to hatch.
