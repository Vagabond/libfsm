/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Nl_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[19] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 19; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xe3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[4], 0xea)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[5], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[6], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[10], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[11], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[9], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[8], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[12], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[13], 0x92)) { goto error; }
	for (i = 0xae; i <= 0xb0; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[7], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[7], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[9], s[7], 0x87)) { goto error; }
	for (i = 0xa1; i <= 0xa9; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[7], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[7], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[7], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[7], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[12], s[14], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[15], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[16], 0x8f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[17], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[18], 0x91)) { goto error; }
	for (i = 0x80; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[14], s[7], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[15], s[7], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[7], 0x8a)) { goto error; }
	for (i = 0x91; i <= 0x95; i++) {
		if (!fsm_addedge_literal(fsm, s[16], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[17], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[18], s[7], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[7], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}
