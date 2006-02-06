/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* DbSources.cc  wrapper for zmd.db 'catalogs' table
 *
 * Copyright (C) 2000-2002 Ximian, Inc.
 * Copyright (C) 2005 SUSE Linux Products GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <iostream>

#include "zypp/base/Logger.h"
#include "zypp/base/Exception.h"

#include "zypp/Source.h"
#include "zypp/SourceFactory.h"
#include "zypp/SourceManager.h"
#include "zypp/source/SourceImpl.h"

#include "zypp/media/MediaManager.h"

#include "DbSources.h"
#include "DbSourceImpl.h"
#include <sqlite3.h>

using namespace std;
using namespace zypp;

//---------------------------------------------------------------------------

DbSources::DbSources (sqlite3 *db)
    : _db (db)
{
}

DbSources::~DbSources ()
{
}

const SourcesList &
DbSources::sources (bool refresh)
{
    MIL << "DbSources::sources(" << (refresh ? "refresh" : "") << ")" << endl;

    if (!refresh
	&& !_sources.empty())
    {
	return _sources;
    }

    _sources.clear();

    media::MediaManager mmgr;
    media::MediaId mediaid = mmgr.open(Url("file://"));

    const char *query =
        "SELECT id, name, alias, description, priority, priority_unsubd "
        "FROM catalogs";

    sqlite3_stmt *handle = NULL;
    int rc = sqlite3_prepare (_db, query, -1, &handle, NULL);
    if (rc != SQLITE_OK) {
	ERR << "Can not read 'channels': " << sqlite3_errmsg (_db) << endl;
	goto cleanup;
    }

    while ((rc = sqlite3_step (handle)) == SQLITE_ROW) {
	string id ((const char *) sqlite3_column_text (handle, 0));
	string name ((const char *) sqlite3_column_text (handle, 1));
        string alias ((const char *) sqlite3_column_text (handle, 2));
        string desc ((const char *) sqlite3_column_text (handle, 3));
	unsigned priority = sqlite3_column_int (handle, 4);
	unsigned priority_unsub = sqlite3_column_int (handle, 5);

	MIL << "id " << id
	    << ", name " << name
	    << ", alias " << alias
	    << ", desc " << desc
	    << ", prio " << priority
	    << ", pr. un" << priority_unsub
	    << endl;
#if 0

	try {

	    Source_Ref::Impl_Ptr impl = new DbSourceImpl (mediaid, pathname, alias);
	    impl->setId( id );
	    impl->setName( name );
	    impl->setPriority( priority );
	    impl->setPriorityUnsubscribed( priority_unsub );
	    SourceFactory _f;
	    Source_Ref s = _f.createFrom( impl );
	}
	catch (Exception & excpt_r) {
	    ZYPP_CAUGHT(excpt_r);
	}
        if (!strcmp (rc_channel_get_id (ch), "@system")) {
            rc_channel_set_system (ch);
            rc_channel_set_hidden (ch);
        }
#endif
    }

    if (rc != SQLITE_DONE) {
	ERR << "Error while reading 'channels': " << sqlite3_errmsg (_db) << endl;
	_sources.clear();
        goto cleanup;
    }

 cleanup:
    if (handle)
        sqlite3_finalize (handle);

    return _sources;
}
