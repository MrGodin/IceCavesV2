#pragma once

static const int iLevel2Width = (130 * 64);
static const int iLevel2Height = (12 * 3) * 64;
static const int iLevel1Width = (130 * 64) * 3;
static const int iLevel1Height = (12 * 64);


static  char* pLevel1String =
"\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B                                                                                                                                                                                                                                                                                                                                                                                                    B\
B                                                                                                                                                                                                                                                                                                                                                                                                    B\
B                                                     Q             ?                                                                                                                                                                                                                                                                                                                                B\
B                     ?                                             Q                                                                                                                                                                                                                                                                                                                                B\
B                                     C       C                                                                                                                                                                                                                                                                                                                                                      B\
B                                         ?                 Q      Q                                                                                                                                                                                                                                                                                                                                 B\
B                                        CC                                                                                                                                                                                                                                                                                                                                                          B\
B               C                                                 Q                                                                                                                                                                                                                                                                                                                                  B\
B       Q     LBBBR                                  LR                                                                                                                                                                                                                                                                                                                                              B\
B            LBBBBBR                                LBBR                                                                                                                                                                                                                                                                                                                                             B\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB";






static  char* pLevel2String =
"\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B                                     B                                                                                          B\
B           1                         B                                                                                          B\
B     QQQQQQQQQQQ                     B                                                                P        1    ZZZ         B\
B                                     B                 1                                                     ZZZZ               B\
B         1P                          B     Z  ZWZ     ZZZZ                                              X          SSSSS        B\
B        ZZZ             2 P1 P       B 1  Z    B   S  P                X      1 P 1             Z     ZSSZ      1          1    B\
B            ZZ          ZZZZZZZ      QZZR   Z ZB     SSSS                    LWWWWR                           ZZZZZ      ZZZZ   B\
B        P ZZ        2  P   0  P 0       QZZ    B             1        SSS    QQQQQQ                             1    Z          B\
B     P  S       P  LZZZZZZSZZZZZZR        2 ZCCBCC   P     LZZZR                     LR                       C LR     LR 1     B\
B  0  LR    PP  ZZZZB P          BBR      LZZQQQQQQZZZZZZZZZQ   QZR    222  LWR     LBBBR                    LWBWBBWR  LZZZRZ    B\
BWWWWWBBWWWWWWWWBBBBBWWWWWWWWWWWWBBBWWWWWWQ                       QWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBBBBWWWWWWWZ    B\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ                         QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ    BB\
B                                                                                   Q                                         Z  B\
B                                                                               1 QQQ                          1     ZZZ    Z    B\
B                                                                             ZZR   QQ                        ZZZZ      1        B\
B                                                      ZZZZ                 W   QR  QQQ                             SSSSS        B\
B     ZZ                                                                    Q    QR   QQ        X                          ZZ    B\
B        ZZZ                 P                     S   X                WW      A QR    Q       Z     ZSSZ      1P2         X    B\
B            ZZ          ZZZZZZZ      ZZZZ            SSSS              QQ    LWWWWQRR                         ZZZZZ      ZZZZ   B\
B          ZZ          P                        P             P      ZZ       QQQQQ QQR                               Z          B\
B        S          LZZZZZZSZZZZZZR           CCCCC         LWWWR                     LR                                LR       B\
B     LR       LZZZZB  P          BWR      LWWBBBBBZZZZZZZZWBBBBBWWR         LWR     LBBR      1           1         1 LZZZR 1   B\
B    ZZZZZZZZZZBBBBBBWWWWWWWWWWWWWBBBZZZZZZBBBBBBBBBBBBBBBBBBBBBBBBBZZZZZZZZZBBBZZZZZBBBBCCCCCCCCCC    CCCCCCZZZZZZZZZZBBBBBZZZZZB\
B   ZQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ   ZQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B Z                                                                                              B   Z                           B\
B  Z                                                                                             ZZZZ                            B\
B   Z                                                                                                                            B\
B  ZZZ                                                 ZZZZ                                                         SSSSS        B\
B     ZZ                                                                                        X                          ZZ    B\
B        ZZZ                 PP                    S                                            Z     ZSSZ                       B\
B            ZZ          ZZZZZZZ      ZZZZ            SSSS                    LWWWWR                           ZZZZZ      ZZZZ   B\
B          ZZ           P    P                  X             X        SSS    QQQQQQ                                  Z          B\
B        S          LZZZZZZSZZZZZZR           CCCCC         LWWWR                     LR                       C LR     LR       B\
B     LR       LZZZZB  P          BWR      LWWBBBBBZZZZZZZZWBBBBBWWR         LWR     LBBR                    LWBWBBWR  LZZZR     B\
QZZZZZZZZZZZZZZBBBBBBWWWWWWWWWWWWWBBBZZZZZZBBBBBBBBBBBBBBBBBBBBBBBBBZZZZZZZZZBBBZZZZZBBBBCCCCCCCCCCCCCCCCCCCCBBBBBBBBZZBBBBBZZZZZQ";
