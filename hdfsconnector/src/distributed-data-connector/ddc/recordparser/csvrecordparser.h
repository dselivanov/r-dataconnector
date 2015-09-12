#ifndef DDC_RECORDPARSER_CSVRECORDPARSER_H
#define DDC_RECORDPARSER_CSVRECORDPARSER_H

#include <map>
#include <string>
#include <boost/variant.hpp>
#include "base/iobserver.h"
#include "irecordparser.h"
#include "splitproducer/split.h"
#include "text/csv/rows.hpp"

namespace ddc {
namespace recordparser {

typedef boost::variant<bool, int32_t, int64_t,double,std::string> CsvVariant;

struct CsvRecord {
    CsvRecord() : isNull(false)
    {
    }
    explicit CsvRecord(const bool _isNull)
    {
        isNull = _isNull;
    }
    CsvRecord(const bool _isNull, const CsvVariant _value)
    {
        isNull = _isNull;
        value = _value;
    }

    bool isNull;
    CsvVariant value;
};

class CsvRecordParser : public IRecordParser
{
public:
    CsvRecordParser();
    ~CsvRecordParser();

    void configure(base::ConfigurationMap &conf);

    boost::any next();
    bool hasNext();

private:
    splitproducer::Split currentSplit_;
//    std::string line_;
//    std::istringstream ss_;
//    text::csv::csv_istream is_;
    text::csv::row row_;
    int32_t rowIndex_;
    std::map<int32_t, std::pair<std::string,std::string> > schema_;
    splitproducer::ISplitProducerPtr splitProducer_;
    bool configured_;
    uint64_t recordsProduced_;
    char delimiter_;
    char commentCharacter_;
    uint64_t commentLinesDiscarded_;
    uint64_t blankLinesDiscarded_;
};

} // namespace recordparsing
} // namespace ddc

#endif // DDC_RECORDPARSER_CSVRECORDPARSER_H