#ifndef __DS1775_H
#define __DS1775_H

#include "main.h"
#include "ds1775_i2c.h"

#define DS1775_COEF_9BIT	(0.00390625F)

float ds1775_get_temperature(void);

#endif /*__DS1775_H */
