uint16_t m_internetTime = 900; // Buffer time to let internet connect
uint8_t m_JP_EU_US = 2; // 0 = JP, 1 = EU, 2 = US
bool m_skip3Days = false; // Re-roll after each raid
bool m_unsafeDC = false;  // Necessary for re-rolling, don't use otherwise
bool m_useLinkCode = false;
bool m_useRandomCode = false;
uint8_t m_seed = 79; // This number will determine the "random" sequence
uint8_t m_linkCode[] = {0,6,9,0}; // Set link code when not using random
uint8_t m_waitTime = 0;  // 0 to wait until 2-min, 1 to wait until 1-min
bool m_addFriends = true; // Add friends between raids
uint8_t m_profile = 1; // If you have multiple profiles, use this to specify which to use
bool m_alternate = false; // Set this to true to alternate between FFA and coded
