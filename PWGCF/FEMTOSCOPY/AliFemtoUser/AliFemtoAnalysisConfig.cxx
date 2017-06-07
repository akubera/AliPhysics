///
/// \file AliFemtoAnalysisConfig.cxx
///

#include "AliFemtoAnalysisConfig.h"

#include <map>
#include <regex>


struct AliFemtoAnalysisConfig::Node {

};

namespace AliFemtoAnalysisConfigParser {

    struct BareValue {};

    template <typename T>
    struct TypedValue : public BareValue {

    };

    typedef TypedValue<double> NumberValue;
    typedef TypedValue<TString> StringValue;


    struct RangeValue {
        double low;
        double high;
    };

    ///
    struct ParsingState {

    };

    struct ParsingToken {

    };



}

static std::regex CONFIG_REGEX("(:(\\{)|)");
// static std::regex NAMESTART_CHAR("[a-zA-Z_]"),
                // ;


///
