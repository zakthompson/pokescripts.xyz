# Instructions

1. Make sure you configure the number of friends you want to delete in the `Config.h` file in this folder
2. Make sure to clear out "new" friends by hovering over them at least once, exiting the friend list, and the returning
3. Place your cursor on the last friend in your list
4. Plug in the bot in to start deleting friends

**Note:** The Switch orders your friends as follows:

* Online best friends
* Online non-best friends
* Offline best friends
* Offline non-best friends

If you wish to delete your online non-best friends, you will need to start your cursor at the **first** friend you wish to delete. Make sure you have your count right, or else you may delete some offline best friends!

## Configuration Options

### m_deleteCount
The number of friends you wish to delete

### m_addFriend
You can optionally accept all friend requests after deleting friends. If you would like to do that, set this to `true` - otherwise, set it to `false`.
