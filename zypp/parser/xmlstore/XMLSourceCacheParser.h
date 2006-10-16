/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/target/store/xmlstore/XMLSourceCacheParser.h
 *
*/

#ifndef XMLSourceCacheParser_h
#define XMLSourceCacheParser_h

#include <zypp/source/SourceInfo.h>
#include <zypp/parser/XMLNodeIterator.h>
#include <zypp/parser/LibXMLHelper.h>
#include <list>

namespace zypp
{
namespace parser
{
namespace xmlstore
{
     typedef shared_ptr<source::SourceInfo> SourceInfo_Ptr;

     /*
      * Use this class as an iterator that produces, one after one,
      * XMLSourceCacheData_Ptr(s) for the XML group elements.
      * Here's an example:
      *
      * for (XMLSourceCacheParser iter(anIstream, baseUrl),
      *      iter != XMLSourceCacheParser.end(),     // or: iter() != 0, or ! iter.atEnd()
      *      ++iter) {
      *    doSomething(*iter)
      * }
      *
      * The iterator owns the pointer (i.e., caller must not delete it)
      * until the next ++ operator is called. At this time, it will be
      * destroyed (and a new ENTRYTYPE is created.)
      *
      * If the input is fundamentally flawed so that it makes no sense to
      * continue parsing, XMLNodeIterator will log it and consider the input as finished.
      * You can query the exit status with errorStatus().
      */

      class XMLSourceCacheParser : public zypp::parser::XMLNodeIterator<SourceInfo_Ptr>
      {
      public:
        XMLSourceCacheParser(std::istream &is, const std::string &baseUrl);
        XMLSourceCacheParser();
        XMLSourceCacheParser(SourceInfo_Ptr & entry);
        virtual ~XMLSourceCacheParser();

      private:
        virtual bool isInterested(const xmlNodePtr nodePtr);
        virtual SourceInfo_Ptr process(const xmlTextReaderPtr reader);
        void parseSourceList(SourceInfo_Ptr dataPtr, xmlNodePtr node);
        zypp::parser::LibXMLHelper _helper;
      };
  } // namespace parser
} // namespace xmlstore
} // namespace zypp

#endif
