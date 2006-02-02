
/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* ProblemSolution.cc
 *
 * Easy-to use interface to the ZYPP dependency resolver
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

#include "zypp/base/String.h"
#include "zypp/base/Gettext.h"
#include "zypp/base/Logger.h"
#include "zypp/solver/detail/ProblemSolutionIgnore.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////
namespace zypp
{ ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
  namespace solver
  { /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    namespace detail
    { ///////////////////////////////////////////////////////////////////

IMPL_PTR_TYPE(ProblemSolutionIgnoreConflicts);
IMPL_PTR_TYPE(ProblemSolutionIgnoreRequires);
IMPL_PTR_TYPE(ProblemSolutionIgnoreArch);

//---------------------------------------------------------------------------

ProblemSolutionIgnoreRequires::ProblemSolutionIgnoreRequires( ResolverProblem_Ptr parent,
							      PoolItem_Ref item,
							      const Capability & capability)
    : ProblemSolution (parent, "", "")
{
	_description = _("Ignoring this requirement");
	addAction ( new InjectSolutionAction (item, capability, REQUIRES));
}

ProblemSolutionIgnoreConflicts::ProblemSolutionIgnoreConflicts( ResolverProblem_Ptr parent,
								PoolItem_Ref item,
								const Capability & capability,
								PoolItem_Ref otherItem)
    : ProblemSolution (parent, "", "")
{
	// TranslatorExplanation %s = name of package, patch, selection ...
	_description = str::form (_("Ignoring conflict of %s"),
				  item->name().c_str());
	addAction (new InjectSolutionAction (item, capability, CONFLICTS, otherItem));	
}

ProblemSolutionIgnoreArch::ProblemSolutionIgnoreArch( ResolverProblem_Ptr parent,
						      PoolItem_Ref item )
    : ProblemSolution (parent, "", "")
{
    _description = _("Ignoring Architecture");
    addAction ( new InjectSolutionAction (item, Capability(), ARCHITECTURE));
}
	
      ///////////////////////////////////////////////////////////////////
    };// namespace detail
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
  };// namespace solver
  ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////
};// namespace zypp
/////////////////////////////////////////////////////////////////////////
