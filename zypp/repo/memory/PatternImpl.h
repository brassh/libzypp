/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/repository/memory/PatternImpl.h
 *
*/
#ifndef ZYPP_DETAIL_MEMORY_PATTERNIMPL_H
#define ZYPP_DETAIL_MEMORY_PATTERNIMPL_H

#include "zypp/detail/PatternImplIf.h"
#include "zypp/data/ResolvableData.h"
#include "zypp/Source.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace repo
  { /////////////////////////////////////////////////////////////////
    namespace memory
    {

      ///////////////////////////////////////////////////////////////////
      //
      //	CLASS NAME : PatternImpl
      //
      /**
      */
      struct PatternImpl : public zypp::detail::PatternImplIf
      {
      public:
        PatternImpl( repo::memory::RepoImpl::Ptr repo, data::Pattern_Ptr ptr);
        virtual ~PatternImpl();

        virtual TranslatedText summary() const;
        virtual TranslatedText description() const;
        virtual TranslatedText insnotify() const;
        virtual TranslatedText delnotify() const;
        virtual TranslatedText licenseToConfirm() const;
        virtual Vendor vendor() const;
        virtual ByteCount size() const;
        virtual ByteCount archivesize() const;
        virtual bool installOnly() const;
        virtual Date buildtime() const;
        virtual Date installtime() const;
        virtual unsigned mediaNr() const;
        
        virtual bool userVisible() const;
        virtual Label order() const;
        virtual Pathname icon() const;
      private:
        
        //ResObject
        TranslatedText _summary;
        TranslatedText _description;
        TranslatedText _insnotify;
        TranslatedText _delnotify;
        TranslatedText _license_to_confirm;
        Vendor _vendor;
        ByteCount _size;
        ByteCount _archivesize;
        bool _install_only;
        Date _buildtime;
        Date _installtime;
        unsigned _media_nr;
        
        // Pattern
        TranslatedText _category;
        bool           _visible;
        std::string    _order;
        Pathname       _icon;
      };
      ///////////////////////////////////////////////////////////////////

      /////////////////////////////////////////////////////////////////
    } // namespace memory
    ///////////////////////////////////////////////////////////////////
  } // namespace repository
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_DETAIL_PATTERNIMPL_H
