// Copyright (c) 2005-2023 Code Synthesis.
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis gives permission
// to link this program with the Xerces-C++ library (or with modified
// versions of Xerces-C++ that use the same license as Xerces-C++), and
// distribute linked combinations including the two. You must obey the GNU
// General Public License version 2 in all respects for all of the code
// used other than Xerces-C++. If you modify this copy of the program, you
// may extend this exception to your version of the program, but you are
// not obligated to do so. If you do not wish to do so, delete this
// exception statement from your version.
//
// Furthermore, Code Synthesis makes a special exception for the Free/Libre
// and Open Source Software (FLOSS) which is described in the accompanying
// FLOSSE file.
//

#ifndef INPUT_SCHEMA_HXX
#define INPUT_SCHEMA_HXX

#ifndef XSD_CXX11
#define XSD_CXX11
#endif

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION!=4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< char, type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  typedef ::xsd::cxx::tree::content_order content_order;
  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::unique_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class FileWriterParametersType;
class SimulationParametersType;
class ThermostatParametersType;
class LinkedCellsParametersType;
class BoundaryParametersType;
class CuboidType;
class DiscType;
class BoundaryType;
class Simulation;

#include <memory>    // ::std::unique_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search
#include <utility>   // std::move

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class FileWriterParametersType: public ::xml_schema::type
{
  public:
  // BaseName
  //
  typedef ::xml_schema::string BaseName_type;
  typedef ::xsd::cxx::tree::traits< BaseName_type, char > BaseName_traits;

  const BaseName_type&
  BaseName () const;

  BaseName_type&
  BaseName ();

  void
  BaseName (const BaseName_type& x);

  void
  BaseName (::std::unique_ptr< BaseName_type > p);

  // WriteFrequency
  //
  typedef ::xml_schema::int_ WriteFrequency_type;
  typedef ::xsd::cxx::tree::traits< WriteFrequency_type, char > WriteFrequency_traits;

  const WriteFrequency_type&
  WriteFrequency () const;

  WriteFrequency_type&
  WriteFrequency ();

  void
  WriteFrequency (const WriteFrequency_type& x);

  // Constructors.
  //
  FileWriterParametersType (const BaseName_type&,
                            const WriteFrequency_type&);

  FileWriterParametersType (const ::xercesc::DOMElement& e,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  FileWriterParametersType (const FileWriterParametersType& x,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  virtual FileWriterParametersType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  FileWriterParametersType&
  operator= (const FileWriterParametersType& x);

  virtual 
  ~FileWriterParametersType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< BaseName_type > BaseName_;
  ::xsd::cxx::tree::one< WriteFrequency_type > WriteFrequency_;
};

class SimulationParametersType: public ::xml_schema::type
{
  public:
  // EndT
  //
  typedef ::xml_schema::double_ EndT_type;
  typedef ::xsd::cxx::tree::traits< EndT_type, char, ::xsd::cxx::tree::schema_type::double_ > EndT_traits;

  const EndT_type&
  EndT () const;

  EndT_type&
  EndT ();

  void
  EndT (const EndT_type& x);

  // DeltaT
  //
  typedef ::xml_schema::double_ DeltaT_type;
  typedef ::xsd::cxx::tree::traits< DeltaT_type, char, ::xsd::cxx::tree::schema_type::double_ > DeltaT_traits;

  const DeltaT_type&
  DeltaT () const;

  DeltaT_type&
  DeltaT ();

  void
  DeltaT (const DeltaT_type& x);

  // Gravity
  //
  typedef ::xml_schema::double_ Gravity_type;
  typedef ::xsd::cxx::tree::optional< Gravity_type > Gravity_optional;
  typedef ::xsd::cxx::tree::traits< Gravity_type, char, ::xsd::cxx::tree::schema_type::double_ > Gravity_traits;

  const Gravity_optional&
  Gravity () const;

  Gravity_optional&
  Gravity ();

  void
  Gravity (const Gravity_type& x);

  void
  Gravity (const Gravity_optional& x);

  // Dimension
  //
  typedef ::xml_schema::int_ Dimension_type;
  typedef ::xsd::cxx::tree::traits< Dimension_type, char > Dimension_traits;

  const Dimension_type&
  Dimension () const;

  Dimension_type&
  Dimension ();

  void
  Dimension (const Dimension_type& x);

  // Constructors.
  //
  SimulationParametersType (const EndT_type&,
                            const DeltaT_type&,
                            const Dimension_type&);

  SimulationParametersType (const ::xercesc::DOMElement& e,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  SimulationParametersType (const SimulationParametersType& x,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  virtual SimulationParametersType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  SimulationParametersType&
  operator= (const SimulationParametersType& x);

  virtual 
  ~SimulationParametersType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< EndT_type > EndT_;
  ::xsd::cxx::tree::one< DeltaT_type > DeltaT_;
  Gravity_optional Gravity_;
  ::xsd::cxx::tree::one< Dimension_type > Dimension_;
};

class ThermostatParametersType: public ::xml_schema::type
{
  public:
  // StartTemperature
  //
  typedef ::xml_schema::double_ StartTemperature_type;
  typedef ::xsd::cxx::tree::traits< StartTemperature_type, char, ::xsd::cxx::tree::schema_type::double_ > StartTemperature_traits;

  const StartTemperature_type&
  StartTemperature () const;

  StartTemperature_type&
  StartTemperature ();

  void
  StartTemperature (const StartTemperature_type& x);

  // TargetTemperature
  //
  typedef ::xml_schema::double_ TargetTemperature_type;
  typedef ::xsd::cxx::tree::traits< TargetTemperature_type, char, ::xsd::cxx::tree::schema_type::double_ > TargetTemperature_traits;

  const TargetTemperature_type&
  TargetTemperature () const;

  TargetTemperature_type&
  TargetTemperature ();

  void
  TargetTemperature (const TargetTemperature_type& x);

  // ApplyFrequency
  //
  typedef ::xml_schema::int_ ApplyFrequency_type;
  typedef ::xsd::cxx::tree::traits< ApplyFrequency_type, char > ApplyFrequency_traits;

  const ApplyFrequency_type&
  ApplyFrequency () const;

  ApplyFrequency_type&
  ApplyFrequency ();

  void
  ApplyFrequency (const ApplyFrequency_type& x);

  // MaxDeltaTemperature
  //
  typedef ::xml_schema::double_ MaxDeltaTemperature_type;
  typedef ::xsd::cxx::tree::traits< MaxDeltaTemperature_type, char, ::xsd::cxx::tree::schema_type::double_ > MaxDeltaTemperature_traits;

  const MaxDeltaTemperature_type&
  MaxDeltaTemperature () const;

  MaxDeltaTemperature_type&
  MaxDeltaTemperature ();

  void
  MaxDeltaTemperature (const MaxDeltaTemperature_type& x);

  // Dimension
  //
  typedef ::xml_schema::int_ Dimension_type;
  typedef ::xsd::cxx::tree::traits< Dimension_type, char > Dimension_traits;

  const Dimension_type&
  Dimension () const;

  Dimension_type&
  Dimension ();

  void
  Dimension (const Dimension_type& x);

  // Constructors.
  //
  ThermostatParametersType (const StartTemperature_type&,
                            const TargetTemperature_type&,
                            const ApplyFrequency_type&,
                            const MaxDeltaTemperature_type&,
                            const Dimension_type&);

  ThermostatParametersType (const ::xercesc::DOMElement& e,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  ThermostatParametersType (const ThermostatParametersType& x,
                            ::xml_schema::flags f = 0,
                            ::xml_schema::container* c = 0);

  virtual ThermostatParametersType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  ThermostatParametersType&
  operator= (const ThermostatParametersType& x);

  virtual 
  ~ThermostatParametersType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< StartTemperature_type > StartTemperature_;
  ::xsd::cxx::tree::one< TargetTemperature_type > TargetTemperature_;
  ::xsd::cxx::tree::one< ApplyFrequency_type > ApplyFrequency_;
  ::xsd::cxx::tree::one< MaxDeltaTemperature_type > MaxDeltaTemperature_;
  ::xsd::cxx::tree::one< Dimension_type > Dimension_;
};

class LinkedCellsParametersType: public ::xml_schema::type
{
  public:
  // LinkedCellsUsed
  //
  typedef ::xml_schema::boolean LinkedCellsUsed_type;
  typedef ::xsd::cxx::tree::traits< LinkedCellsUsed_type, char > LinkedCellsUsed_traits;

  const LinkedCellsUsed_type&
  LinkedCellsUsed () const;

  LinkedCellsUsed_type&
  LinkedCellsUsed ();

  void
  LinkedCellsUsed (const LinkedCellsUsed_type& x);

  // CutoffRadius
  //
  typedef ::xml_schema::double_ CutoffRadius_type;
  typedef ::xsd::cxx::tree::traits< CutoffRadius_type, char, ::xsd::cxx::tree::schema_type::double_ > CutoffRadius_traits;

  const CutoffRadius_type&
  CutoffRadius () const;

  CutoffRadius_type&
  CutoffRadius ();

  void
  CutoffRadius (const CutoffRadius_type& x);

  // Constructors.
  //
  LinkedCellsParametersType (const LinkedCellsUsed_type&,
                             const CutoffRadius_type&);

  LinkedCellsParametersType (const ::xercesc::DOMElement& e,
                             ::xml_schema::flags f = 0,
                             ::xml_schema::container* c = 0);

  LinkedCellsParametersType (const LinkedCellsParametersType& x,
                             ::xml_schema::flags f = 0,
                             ::xml_schema::container* c = 0);

  virtual LinkedCellsParametersType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  LinkedCellsParametersType&
  operator= (const LinkedCellsParametersType& x);

  virtual 
  ~LinkedCellsParametersType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< LinkedCellsUsed_type > LinkedCellsUsed_;
  ::xsd::cxx::tree::one< CutoffRadius_type > CutoffRadius_;
};

class BoundaryParametersType: public ::xml_schema::type
{
  public:
  // Domain
  //
  typedef ::xml_schema::string Domain_type;
  typedef ::xsd::cxx::tree::traits< Domain_type, char > Domain_traits;

  const Domain_type&
  Domain () const;

  Domain_type&
  Domain ();

  void
  Domain (const Domain_type& x);

  void
  Domain (::std::unique_ptr< Domain_type > p);

  // TOP
  //
  typedef ::BoundaryType TOP_type;
  typedef ::xsd::cxx::tree::traits< TOP_type, char > TOP_traits;

  const TOP_type&
  TOP () const;

  TOP_type&
  TOP ();

  void
  TOP (const TOP_type& x);

  void
  TOP (::std::unique_ptr< TOP_type > p);

  // RIGHT
  //
  typedef ::BoundaryType RIGHT_type;
  typedef ::xsd::cxx::tree::traits< RIGHT_type, char > RIGHT_traits;

  const RIGHT_type&
  RIGHT () const;

  RIGHT_type&
  RIGHT ();

  void
  RIGHT (const RIGHT_type& x);

  void
  RIGHT (::std::unique_ptr< RIGHT_type > p);

  // BOTTOM
  //
  typedef ::BoundaryType BOTTOM_type;
  typedef ::xsd::cxx::tree::traits< BOTTOM_type, char > BOTTOM_traits;

  const BOTTOM_type&
  BOTTOM () const;

  BOTTOM_type&
  BOTTOM ();

  void
  BOTTOM (const BOTTOM_type& x);

  void
  BOTTOM (::std::unique_ptr< BOTTOM_type > p);

  // LEFT
  //
  typedef ::BoundaryType LEFT_type;
  typedef ::xsd::cxx::tree::traits< LEFT_type, char > LEFT_traits;

  const LEFT_type&
  LEFT () const;

  LEFT_type&
  LEFT ();

  void
  LEFT (const LEFT_type& x);

  void
  LEFT (::std::unique_ptr< LEFT_type > p);

  // FRONT
  //
  typedef ::BoundaryType FRONT_type;
  typedef ::xsd::cxx::tree::traits< FRONT_type, char > FRONT_traits;

  const FRONT_type&
  FRONT () const;

  FRONT_type&
  FRONT ();

  void
  FRONT (const FRONT_type& x);

  void
  FRONT (::std::unique_ptr< FRONT_type > p);

  // BACK
  //
  typedef ::BoundaryType BACK_type;
  typedef ::xsd::cxx::tree::traits< BACK_type, char > BACK_traits;

  const BACK_type&
  BACK () const;

  BACK_type&
  BACK ();

  void
  BACK (const BACK_type& x);

  void
  BACK (::std::unique_ptr< BACK_type > p);

  // Constructors.
  //
  BoundaryParametersType (const Domain_type&,
                          const TOP_type&,
                          const RIGHT_type&,
                          const BOTTOM_type&,
                          const LEFT_type&,
                          const FRONT_type&,
                          const BACK_type&);

  BoundaryParametersType (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f = 0,
                          ::xml_schema::container* c = 0);

  BoundaryParametersType (const BoundaryParametersType& x,
                          ::xml_schema::flags f = 0,
                          ::xml_schema::container* c = 0);

  virtual BoundaryParametersType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  BoundaryParametersType&
  operator= (const BoundaryParametersType& x);

  virtual 
  ~BoundaryParametersType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< Domain_type > Domain_;
  ::xsd::cxx::tree::one< TOP_type > TOP_;
  ::xsd::cxx::tree::one< RIGHT_type > RIGHT_;
  ::xsd::cxx::tree::one< BOTTOM_type > BOTTOM_;
  ::xsd::cxx::tree::one< LEFT_type > LEFT_;
  ::xsd::cxx::tree::one< FRONT_type > FRONT_;
  ::xsd::cxx::tree::one< BACK_type > BACK_;
};

class CuboidType: public ::xml_schema::type
{
  public:
  // Coordinates
  //
  typedef ::xml_schema::string Coordinates_type;
  typedef ::xsd::cxx::tree::traits< Coordinates_type, char > Coordinates_traits;

  const Coordinates_type&
  Coordinates () const;

  Coordinates_type&
  Coordinates ();

  void
  Coordinates (const Coordinates_type& x);

  void
  Coordinates (::std::unique_ptr< Coordinates_type > p);

  // ParticlesPerDimension
  //
  typedef ::xml_schema::string ParticlesPerDimension_type;
  typedef ::xsd::cxx::tree::traits< ParticlesPerDimension_type, char > ParticlesPerDimension_traits;

  const ParticlesPerDimension_type&
  ParticlesPerDimension () const;

  ParticlesPerDimension_type&
  ParticlesPerDimension ();

  void
  ParticlesPerDimension (const ParticlesPerDimension_type& x);

  void
  ParticlesPerDimension (::std::unique_ptr< ParticlesPerDimension_type > p);

  // Distance
  //
  typedef ::xml_schema::double_ Distance_type;
  typedef ::xsd::cxx::tree::traits< Distance_type, char, ::xsd::cxx::tree::schema_type::double_ > Distance_traits;

  const Distance_type&
  Distance () const;

  Distance_type&
  Distance ();

  void
  Distance (const Distance_type& x);

  // Mass
  //
  typedef ::xml_schema::double_ Mass_type;
  typedef ::xsd::cxx::tree::traits< Mass_type, char, ::xsd::cxx::tree::schema_type::double_ > Mass_traits;

  const Mass_type&
  Mass () const;

  Mass_type&
  Mass ();

  void
  Mass (const Mass_type& x);

  // InitialVelocities
  //
  typedef ::xml_schema::string InitialVelocities_type;
  typedef ::xsd::cxx::tree::traits< InitialVelocities_type, char > InitialVelocities_traits;

  const InitialVelocities_type&
  InitialVelocities () const;

  InitialVelocities_type&
  InitialVelocities ();

  void
  InitialVelocities (const InitialVelocities_type& x);

  void
  InitialVelocities (::std::unique_ptr< InitialVelocities_type > p);

  // MeanVelocity
  //
  typedef ::xml_schema::double_ MeanVelocity_type;
  typedef ::xsd::cxx::tree::traits< MeanVelocity_type, char, ::xsd::cxx::tree::schema_type::double_ > MeanVelocity_traits;

  const MeanVelocity_type&
  MeanVelocity () const;

  MeanVelocity_type&
  MeanVelocity ();

  void
  MeanVelocity (const MeanVelocity_type& x);

  // Constructors.
  //
  CuboidType (const Coordinates_type&,
              const ParticlesPerDimension_type&,
              const Distance_type&,
              const Mass_type&,
              const InitialVelocities_type&,
              const MeanVelocity_type&);

  CuboidType (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  CuboidType (const CuboidType& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  virtual CuboidType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  CuboidType&
  operator= (const CuboidType& x);

  virtual 
  ~CuboidType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< Coordinates_type > Coordinates_;
  ::xsd::cxx::tree::one< ParticlesPerDimension_type > ParticlesPerDimension_;
  ::xsd::cxx::tree::one< Distance_type > Distance_;
  ::xsd::cxx::tree::one< Mass_type > Mass_;
  ::xsd::cxx::tree::one< InitialVelocities_type > InitialVelocities_;
  ::xsd::cxx::tree::one< MeanVelocity_type > MeanVelocity_;
};

class DiscType: public ::xml_schema::type
{
  public:
  // CenterCoordinates
  //
  typedef ::xml_schema::string CenterCoordinates_type;
  typedef ::xsd::cxx::tree::traits< CenterCoordinates_type, char > CenterCoordinates_traits;

  const CenterCoordinates_type&
  CenterCoordinates () const;

  CenterCoordinates_type&
  CenterCoordinates ();

  void
  CenterCoordinates (const CenterCoordinates_type& x);

  void
  CenterCoordinates (::std::unique_ptr< CenterCoordinates_type > p);

  // InitialVelocities
  //
  typedef ::xml_schema::string InitialVelocities_type;
  typedef ::xsd::cxx::tree::traits< InitialVelocities_type, char > InitialVelocities_traits;

  const InitialVelocities_type&
  InitialVelocities () const;

  InitialVelocities_type&
  InitialVelocities ();

  void
  InitialVelocities (const InitialVelocities_type& x);

  void
  InitialVelocities (::std::unique_ptr< InitialVelocities_type > p);

  // NumberOfParticlesAlongRadius
  //
  typedef ::xml_schema::int_ NumberOfParticlesAlongRadius_type;
  typedef ::xsd::cxx::tree::traits< NumberOfParticlesAlongRadius_type, char > NumberOfParticlesAlongRadius_traits;

  const NumberOfParticlesAlongRadius_type&
  NumberOfParticlesAlongRadius () const;

  NumberOfParticlesAlongRadius_type&
  NumberOfParticlesAlongRadius ();

  void
  NumberOfParticlesAlongRadius (const NumberOfParticlesAlongRadius_type& x);

  // Distance
  //
  typedef ::xml_schema::double_ Distance_type;
  typedef ::xsd::cxx::tree::traits< Distance_type, char, ::xsd::cxx::tree::schema_type::double_ > Distance_traits;

  const Distance_type&
  Distance () const;

  Distance_type&
  Distance ();

  void
  Distance (const Distance_type& x);

  // Mass
  //
  typedef ::xml_schema::double_ Mass_type;
  typedef ::xsd::cxx::tree::traits< Mass_type, char, ::xsd::cxx::tree::schema_type::double_ > Mass_traits;

  const Mass_type&
  Mass () const;

  Mass_type&
  Mass ();

  void
  Mass (const Mass_type& x);

  // Constructors.
  //
  DiscType (const CenterCoordinates_type&,
            const InitialVelocities_type&,
            const NumberOfParticlesAlongRadius_type&,
            const Distance_type&,
            const Mass_type&);

  DiscType (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  DiscType (const DiscType& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual DiscType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  DiscType&
  operator= (const DiscType& x);

  virtual 
  ~DiscType ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< CenterCoordinates_type > CenterCoordinates_;
  ::xsd::cxx::tree::one< InitialVelocities_type > InitialVelocities_;
  ::xsd::cxx::tree::one< NumberOfParticlesAlongRadius_type > NumberOfParticlesAlongRadius_;
  ::xsd::cxx::tree::one< Distance_type > Distance_;
  ::xsd::cxx::tree::one< Mass_type > Mass_;
};

class BoundaryType: public ::xml_schema::string
{
  public:
  enum value
  {
    REFLECTING,
    OUTFLOW,
    PERIODIC,
    OFF
  };

  BoundaryType (value v);

  BoundaryType (const char* v);

  BoundaryType (const ::std::string& v);

  BoundaryType (const ::xml_schema::string& v);

  BoundaryType (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  BoundaryType (const ::xercesc::DOMAttr& a,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  BoundaryType (const ::std::string& s,
                const ::xercesc::DOMElement* e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  BoundaryType (const BoundaryType& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

#ifdef XSD_CXX11
  BoundaryType&
  operator= (const BoundaryType&) = default;
#endif

  virtual BoundaryType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  BoundaryType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_BoundaryType_convert ();
  }

  protected:
  value
  _xsd_BoundaryType_convert () const;

  public:
  static const char* const _xsd_BoundaryType_literals_[4];
  static const value _xsd_BoundaryType_indexes_[4];
};

class Simulation: public ::xml_schema::type
{
  public:
  // FileWriterParameters
  //
  typedef ::FileWriterParametersType FileWriterParameters_type;
  typedef ::xsd::cxx::tree::traits< FileWriterParameters_type, char > FileWriterParameters_traits;

  const FileWriterParameters_type&
  FileWriterParameters () const;

  FileWriterParameters_type&
  FileWriterParameters ();

  void
  FileWriterParameters (const FileWriterParameters_type& x);

  void
  FileWriterParameters (::std::unique_ptr< FileWriterParameters_type > p);

  // SimulationParameters
  //
  typedef ::SimulationParametersType SimulationParameters_type;
  typedef ::xsd::cxx::tree::traits< SimulationParameters_type, char > SimulationParameters_traits;

  const SimulationParameters_type&
  SimulationParameters () const;

  SimulationParameters_type&
  SimulationParameters ();

  void
  SimulationParameters (const SimulationParameters_type& x);

  void
  SimulationParameters (::std::unique_ptr< SimulationParameters_type > p);

  // ThermostatParameters
  //
  typedef ::ThermostatParametersType ThermostatParameters_type;
  typedef ::xsd::cxx::tree::traits< ThermostatParameters_type, char > ThermostatParameters_traits;

  const ThermostatParameters_type&
  ThermostatParameters () const;

  ThermostatParameters_type&
  ThermostatParameters ();

  void
  ThermostatParameters (const ThermostatParameters_type& x);

  void
  ThermostatParameters (::std::unique_ptr< ThermostatParameters_type > p);

  // LinkedCellsParameters
  //
  typedef ::LinkedCellsParametersType LinkedCellsParameters_type;
  typedef ::xsd::cxx::tree::traits< LinkedCellsParameters_type, char > LinkedCellsParameters_traits;

  const LinkedCellsParameters_type&
  LinkedCellsParameters () const;

  LinkedCellsParameters_type&
  LinkedCellsParameters ();

  void
  LinkedCellsParameters (const LinkedCellsParameters_type& x);

  void
  LinkedCellsParameters (::std::unique_ptr< LinkedCellsParameters_type > p);

  // BoundaryParameters
  //
  typedef ::BoundaryParametersType BoundaryParameters_type;
  typedef ::xsd::cxx::tree::traits< BoundaryParameters_type, char > BoundaryParameters_traits;

  const BoundaryParameters_type&
  BoundaryParameters () const;

  BoundaryParameters_type&
  BoundaryParameters ();

  void
  BoundaryParameters (const BoundaryParameters_type& x);

  void
  BoundaryParameters (::std::unique_ptr< BoundaryParameters_type > p);

  // Cuboid
  //
  typedef ::CuboidType Cuboid_type;
  typedef ::xsd::cxx::tree::sequence< Cuboid_type > Cuboid_sequence;
  typedef Cuboid_sequence::iterator Cuboid_iterator;
  typedef Cuboid_sequence::const_iterator Cuboid_const_iterator;
  typedef ::xsd::cxx::tree::traits< Cuboid_type, char > Cuboid_traits;

  const Cuboid_sequence&
  Cuboid () const;

  Cuboid_sequence&
  Cuboid ();

  void
  Cuboid (const Cuboid_sequence& s);

  // Disc
  //
  typedef ::DiscType Disc_type;
  typedef ::xsd::cxx::tree::sequence< Disc_type > Disc_sequence;
  typedef Disc_sequence::iterator Disc_iterator;
  typedef Disc_sequence::const_iterator Disc_const_iterator;
  typedef ::xsd::cxx::tree::traits< Disc_type, char > Disc_traits;

  const Disc_sequence&
  Disc () const;

  Disc_sequence&
  Disc ();

  void
  Disc (const Disc_sequence& s);

  // Constructors.
  //
  Simulation (const FileWriterParameters_type&,
              const SimulationParameters_type&,
              const ThermostatParameters_type&,
              const LinkedCellsParameters_type&,
              const BoundaryParameters_type&);

  Simulation (::std::unique_ptr< FileWriterParameters_type >,
              ::std::unique_ptr< SimulationParameters_type >,
              ::std::unique_ptr< ThermostatParameters_type >,
              ::std::unique_ptr< LinkedCellsParameters_type >,
              ::std::unique_ptr< BoundaryParameters_type >);

  Simulation (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  Simulation (const Simulation& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::container* c = 0);

  virtual Simulation*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  Simulation&
  operator= (const Simulation& x);

  virtual 
  ~Simulation ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< FileWriterParameters_type > FileWriterParameters_;
  ::xsd::cxx::tree::one< SimulationParameters_type > SimulationParameters_;
  ::xsd::cxx::tree::one< ThermostatParameters_type > ThermostatParameters_;
  ::xsd::cxx::tree::one< LinkedCellsParameters_type > LinkedCellsParameters_;
  ::xsd::cxx::tree::one< BoundaryParameters_type > BoundaryParameters_;
  Cuboid_sequence Cuboid_;
  Disc_sequence Disc_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& uri,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& uri,
             ::xml_schema::error_handler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& uri,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xml_schema::error_handler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& id,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& id,
             ::xml_schema::error_handler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& id,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& is,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& is,
             ::xml_schema::error_handler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& is,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::unique_ptr< ::Simulation >
Simulation_ (const ::xercesc::DOMDocument& d,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::Simulation >
Simulation_ (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
             ::xml_schema::flags f = 0,
             const ::xml_schema::properties& p = ::xml_schema::properties ());

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // INPUT_SCHEMA_HXX
