/**
 * @file    nsSJISProber.h
 * @brief   nsSJISProber
 * @license GPL 2.0/LGPL 2.1
 */

// for S-JIS encoding, obeserve characteristic:
// 1, kana character (or hankaku?) often have hight frequency of appereance
// 2, kana character often exist in group
// 3, certain combination of kana is never used in japanese language

#ifndef nsSJISProber_h__
#define nsSJISProber_h__

#include "nsCharSetProber.h"
#include "nsCodingStateMachine.h"
#include "JpCntx.h"
#include "CharDistribution.h"


class nsSJISProber: public nsCharSetProber {
public:
  nsSJISProber(bool aIsPreferredLanguage)
    :mIsPreferredLanguage(aIsPreferredLanguage)
  {mCodingSM = new nsCodingStateMachine(&SJISSMModel);
    Reset();}
  virtual ~nsSJISProber(void){delete mCodingSM;}
  nsProbingState HandleData(const char* aBuf, PRUint32 aLen);
  const char* GetCharSetName() {return "Shift_JIS";}
  nsProbingState GetState(void) {return mState;}
  void      Reset(void);
  float     GetConfidence(void);

protected:
  nsCodingStateMachine* mCodingSM;
  nsProbingState mState;

  SJISContextAnalysis mContextAnalyser;
  SJISDistributionAnalysis mDistributionAnalyser;

  char mLastChar[2];
  bool mIsPreferredLanguage;

};


#endif /* nsSJISProber_h__ */

