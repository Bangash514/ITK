/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    genTclGenerator.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef _genTclGenerator_h
#define _genTclGenerator_h

#include "genGeneratorBase.h"
#include "cableSourceRepresentation.h"
#include "genCvTypeGenerator.h"

namespace gen
{


/**
 * Generation class for Tcl wrappers.
 */
class TclGenerator: public GeneratorBase
{
public:
  TclGenerator(const configuration::Package* in_package,
               const source::Namespace* in_globalNamespace):
    GeneratorBase(in_package), m_GlobalNamespace(in_globalNamespace) {}
  virtual ~TclGenerator() {}
  
  static GeneratorBase* GetInstance(const configuration::Package*,
                                    const source::Namespace*);  
  
  virtual void Generate();  
private:
  typedef std::vector<String> WrapperList;
  typedef std::vector<source::Method*> Methods;
  
  void GeneratePackage(const configuration::Package*);  
  void GenerateIncludes(std::ostream&, const configuration::Headers*);  
  void GenerateNamespace(std::ostream&,
                         const configuration::PackageNamespace*);
  void GenerateWrapperSet(std::ostream&, const configuration::WrapperSet*,
                          const configuration::PackageNamespace*);
  void GenerateClassWrapper(std::ostream&, const source::Class*);
  bool ReturnsVoid(const source::Function*) const;
  void WriteWrapperClassDefinition(std::ostream&, const source::Class*,
                                   const Methods&) const;
  void WriteImplicitArgument(std::ostream&, const source::Class*,
                             const source::Method*) const;
  void WriteArgumentList(std::ostream&, const source::ArgumentContainer&) const;
  void WriteArgumentAs(std::ostream&, const cxx::CvQualifiedType&,
                       unsigned int) const;
  void WriteReturnBegin(std::ostream&, const source::Function*) const;
  void WriteReturnEnd(std::ostream&, const source::Function*) const;
  void FindCvTypes(const configuration::PackageNamespace*);
  void FindCvTypes(const configuration::WrapperSet*,
                   const configuration::PackageNamespace*);
  void FindCvTypes(const source::Class*);
  void FindCvTypes(const source::Method*);
  cxx::CvQualifiedType GetCxxType(const source::Type*) const;

  /**
   * The global namespace that was parsed from the source file.
   */
  const source::Namespace* m_GlobalNamespace;
  
  /**
   * Generator to write out CxxType representation construction code.
   */
  CvTypeGenerator  m_CvTypeGenerator;
  
  WrapperList m_WrapperList;
};

} // namespace gen
  
#endif
