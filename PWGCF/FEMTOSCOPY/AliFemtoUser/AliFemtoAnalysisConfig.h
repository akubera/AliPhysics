///
/// \file AliFemtoAnalysisConfiguration.h
///

#pragma once

#include <TObject.h>
#include <TString.h>


template <bool>
struct config_constructable {};

template <typename T>
T* GetResult(const Result &result, config_constructable<true>) {
   return new T(result);
}

template <typename T>
T* GetResult(const Result &result, config_constructable<true>) {
   return new T(result);
}

template <typename T>
T* GetResult(const Result &result) {
   return GetResult<T>(result, config_constructable<std::is_constructible<T, const AliFemtoAnalysisConfig&>::value> {});
}


/// \class AliFemtoAnalysisConfig
/// \brief Configuration object used to create arbitrary analysis parameters
///
/// Completely parameterize your analysis using this class.
/// To enable this for your class, all you have to do is add a constructor or
/// a static method named `FromConfig` which accepts a const reference to a
/// config value and returns a pointer to your class.
/// See AliFemtoAnalysisPionPion for an example implementation.
///
/// The configuration syntax is similar to JSON, but with extra conveniences.
/// Strings should be quoted with single-quotes, allowing easy-embedding into
/// strings within code.
/// Keys in map objects do not have to be quoted, and may have 'subproperties'
/// separated by dots, so `{a.b: 5}` is equivalent to `{a: {b: 5}}`.
///
/// Ranges can be expressed as numbers separated by double dots, `(0.2 .. 1.0)`.
/// which is shorthand for configuration objects with 'low' and 'high' attributes.
///
///
/// Examples
/// --------
///
/// ```cpp
///   { name : 'AliFemtoConfig', pt: .14 -> 2.0, }
/// ```
///
/// ```cpp
///   AliFemtoAnalysisConfig cfg("{a:1,b:2}");
///   auto gen_analysis = cfg.BuildAnalysis();
///   if (!gen_analysis.IsOk()) {
///     std::cerr << "Error building analysis: " << gen_analsysis.ErrorString() << "\n";
///     return;
///   }
///   AnalysisType *analysis = gen_analysis.value();
/// ```
///
/// \author Andrew Kubera, The Ohio State University, <andrew.michael.kubera@cern.ch>
///
class AliFemtoAnalysisConfig : public TObject {
public:

    /// Result class which holds either a pointer to a generated object,
    /// or an error string.
    ///
    /// This should not be created directly, but used from the BuildAnalysis
    /// method of AliFemtoAnalysisConfig
    ///
    class Result {
    public:
        /// True if valid value was loaded - otherwise
        bool IsOk() const;

        /// Return string explaining problem with configuration.
        /// If no problem, this is the empty string.
        TString ErrorString() const;

        /// Get the built analysis object
        template <typename AnalysisClass>
        AnalysisClass* value();

    protected:
        void *fPtr;
        TString fError;
    };

    /// Internal class used to store configuration data
    class Node;

public:

    /// Build from a source string
    AliFemtoAnalysisConfig(const TString&);

    /// Build an analysis with this configuration
    template <typename AnalysisClass>
    // Result<AnalysisClass> BuildAnalysis() const;
    Result BuildAnalysis() const;

protected:

    // template <typename AnalysisClass, bool>
    // AnalysisClass* value();

    /// Root node of configuration - the type of this node
    /// represents the type of the configuration object
    Node *fRoot;

private:
    /// \cond CLASSIMP
    ClassDef(AliFemtoAnalysisConfig, 0);
    /// \endcond
};

inline bool
AliFemtoAnalysisConfig::Result::IsOk() const
{
  return fPtr != nullptr;
}

inline TString
AliFemtoAnalysisConfig::Result::ErrorString() const
{
  return fError;
}

template <typename AnalysisClass>
AnalysisClass*
AliFemtoAnalysisConfig::Result::value()
{
  return dynamic_cast<AnalysisClass*>(fPtr);
}

/*
template <typename AnalysisClass>
// Result<AnalysisClass> BuildAnalysis() const;
AliFemtoAnalysisConfig::Result AliFemtoAnalysisConfig::BuildAnalysis() const
{
    Result result;
    try {
        AnalysisClass *val = new AnalysisClass(*this);
        result.fPtr = val;
    } catch (const TString& err) {
        result.fError = err;
    }

    return result;
}


template <typename AnalysisClass>
// Result<AnalysisClass> BuildAnalysis() const;
AliFemtoAnalysisConfig::Result AliFemtoAnalysisConfig::BuildAnalysis() const
{
    Result r;
    try {
        AnalysisClass *result = AnalysisClass::FromConfig(*this);
        r.fPtr = result;
    } catch (const TString& err) {
        r.fError = err;
    }

    return r;
}
*/


// template <typename AnalysisClass, true>
// AliFemtoAnalysisConfig::Result AliFemtoAnalysisConfig::BuildAnalysis() const
// {
//     Result result;
//     try {
//         AnalysisClass *val = new AnalysisClass(*this);
//         result.fPtr = val;
//     } catch (const TString& err) {
//         result.fError = err;
//     }

//     return result;
// }



// template <typename AnalysisClass, false>
// AliFemtoAnalysisConfig::Result AliFemtoAnalysisConfig::BuildAnalysis() const
// {
//     Result r;
//     try {
//         AnalysisClass *result = AnalysisClass::FromConfig(*this);
//         r.fPtr = result;
//     } catch (const TString& err) {
//         r.fError = err;
//     }

//     return r;
// }


// template <typename AnalysisClass>
// AliFemtoAnalysisConfig::Result AliFemtoAnalysisConfig::BuildAnalysis() const
// {
//     return AliFemtoAnalysisConfig::BuildAnalysis<
//         AnalysisClass,
//         std::is_constructible<AnalysisClass, const AliFemtoAnalysisConfig&>::value>(this)
// }

