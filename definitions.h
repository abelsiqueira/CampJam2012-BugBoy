#ifndef definitions_h
#define definitions_h

enum Keys { key_left = 0, key_right = 1 };
enum UpgradeType { jumpUpgrade, speedUpgrade, lifeUpgrade,
    doubleJumpUpgrade };

const int cWindowWidth = 1280;
const int cWindowHeight = 720;
const int cFps = 60;
const int cTileSize = 40;
const float cGravity = 0.25;
const int cInvulnerableCountdown = 2*cFps;
const int cShootCooldown = cFps*2/3;

const char cNone       = '.';
const char cBlock      = 'x';
const char cSpike      = '/';
const char cAnt        = 'a';
const char cPlayer     = 'p';
const char cFly        = 'f';
const char cSpider     = 's';
const char cSpiderBoss = 'B';
const char cJump       = 'j';
const char cSpeed      = 'e';
const char cLife       = 'v';
const char cDoubleJump = 'd';

#endif
