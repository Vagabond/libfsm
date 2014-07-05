/* $Id$ */

#include <assert.h>
#include <stddef.h>
#include <limits.h>

#include <fsm/fsm.h>
#include <fsm/graph.h>

#include "internal.h"
#include "set.h"

int
fsm_complete(struct fsm *fsm)
{
	struct fsm_state *new;
	struct fsm_state *s;
	size_t i;

	assert(fsm != NULL);
	assert(fsm_isdfa(fsm));

	if (fsm_iscomplete(fsm)) {
		return 1;
	}

	/*
	 * A DFA is complete when every state has an edge for every symbol in the
	 * alphabet. For a typical low-density FSM, most of these will go to an
	 * "error" state, which is a non-end state that has every edge going back
	 * to itself. That error state is implicit in most FSMs, but rarely
	 * actually drawn. The idea here is to explicitly create it.
	 */

	new = fsm_addstate(fsm);
	if (new == NULL) {
		return 0;
	}

	for (i = 0; i <= UCHAR_MAX; i++) {
		if (!set_addstate(&new->edges[i].sl, new)) {
			/* TODO: free stuff */
			return 0;
		}
	}

	for (s = fsm->sl; s != NULL; s = s->next) {
		for (i = 0; i <= UCHAR_MAX; i++) {
			if (s->edges[i].sl != NULL) {
				continue;
			}

			if (!set_addstate(&s->edges[i].sl, new)) {
				/* TODO: free stuff */
				return 0;
			}
		}
	}

	return 1;
}

int
fsm_iscompletestate(const struct fsm *fsm, const struct fsm_state *state)
{
	size_t i;

	assert(fsm != NULL);
	assert(state != NULL);

	/* TODO: assert state is in fsm->sl */

	for (i = 0; i <= UCHAR_MAX; i++) {
		if (state->edges[i].sl == NULL) {
			return 0;
		}
	}

	return 1;
}

int
fsm_iscomplete(const struct fsm *fsm)
{
	struct fsm_state *s;

	assert(fsm != NULL);

	if (fsm->sl == NULL) {
		return 0;
	}

	for (s = fsm->sl; s != NULL; s = s->next) {
		if (!fsm_iscompletestate(fsm, s)) {
			return 0;
		}
	}

	return 1;
}

