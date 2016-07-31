#ifndef _POSTDROP_H_
#define _POSTDROP_H_
void PDinit(const char *sHostname, const char *sUsername, const char *sPrimary, const char *sOtpsecret);
void PDget(const char *shorturl);
void PDlist();
#endif
