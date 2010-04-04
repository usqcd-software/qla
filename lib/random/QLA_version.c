#include <stdio.h>
#include <qla_config.h>
#include <qla_random.h>

static const char *vs = VERSION;

const char *
QLA_version_str(void)
{
  return vs;
}

int
QLA_version_int(void)
{
  int maj, min, bug;
  sscanf(vs, "%i.%i.%i", &maj, &min, &bug);
  return ((maj*1000)+min)*1000 + bug;
}
