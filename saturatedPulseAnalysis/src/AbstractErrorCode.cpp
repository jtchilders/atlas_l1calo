#include "AbstractErrorCode.h"

bool AbstractErrorCode::bitIsSet(unsigned int number) const {
  unsigned int correspondingNumber = (unsigned int) (1<<number);

  bool isSet( ( m_errorCode & correspondingNumber) > 0);

  return isSet;
}

void AbstractErrorCode::setBit(unsigned int number, bool value) {
  bool isSet(bitIsSet(number));
  unsigned int correspondingNumber = (unsigned int) (1<<number);

  // set bit if not set yet
  if ((value) && (!isSet)) m_errorCode |= correspondingNumber;
  // remove bit if bit is set
  if ((!value) && (isSet)) m_errorCode &= ~correspondingNumber;
}
