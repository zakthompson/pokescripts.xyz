# Instructions

1. Make sure you set all your configuration options!
2. Stand in front of an active den with watts already collected
3. You must be offline when starting the script

## Configuration Options

### m_internetTime
Increase/decrease this number based on how long your Switch takes to connect to the Internet

### m_JP_EU_US
Set your language format if you plan to re-roll between raids. 0 = JP, 1 = EU, 2 = JP

### m_skip3Days
Set to `true` to re-roll between each raid, `false` to keep the same Pokemon

### m_unsafeDC
Uses the "Local Friend Search" method to disconnect from raid. Necessary for re-rolling a den, but less safe - if a raid fires with nobody joining, you won't be disconnected and the bot will mess up

### m_useLinkCode
`true` to use Link Codes, `false` to do free-for-all

### m_useRandomCode
`true` to set a random Link Code each time (you will need to watch to announce). `false` to only use the set Link Code

### m_seed
If using random Link Codes, the codes are generated in a sequence determined by this number. Each time you restart the bot, it will use the same sequence of codes. Changing this number will change the sequence - you can make it something random

### m_linkCode[]
If not using random Link Codes, this is the code that will be used.

### m_waitTime
Set this to `0` to wait until the 2-minute mark before firing the raid, or `1` to wait until the 1-minute mark

### m_addFriends
Set this to `true` to add friends while waiting for people to join the raid. When `false`, no new friends will be added.

### m_profile
If your Switch has mulitple profiles, set this to the profile it should use.  `0` is farthest left, followed by `1`, etc.
