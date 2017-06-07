///
/// \file AliFemtoAnalysisConfiguration.h
///

#pragma once

#include "TObject.h"


/// \class AliFemtoAnalysisConfig
/// \brief Configuration object used to create arbitrary analysis parameters
///
class AliFemtoAnalysisConfig : public TObject {
public:
    /// Result
    template <typename Analysis>
    class Result;

public:

    /// Build from a source string
    AliFemtoAnalysisConfig(const TString&);

    /// Build an analysis with this configuration
    template <typename AnalysisClass>
    Result<AnalysisClass> BuildAnalysis() const;

    /// Build
protected:

private:
/// \cond CLASSIMP
    ClassDef(AliFemtoAnalysisConfig, 0);
/// \endcond
};


template <typename AnalysisClass>
struct AliFemtoAnalysisConfig::Result {

};
