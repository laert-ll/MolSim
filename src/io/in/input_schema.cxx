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

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "input_schema.hxx"

// FileWriterParametersType
//

const FileWriterParametersType::BaseName_type& FileWriterParametersType::
BaseName () const
{
  return this->BaseName_.get ();
}

FileWriterParametersType::BaseName_type& FileWriterParametersType::
BaseName ()
{
  return this->BaseName_.get ();
}

void FileWriterParametersType::
BaseName (const BaseName_type& x)
{
  this->BaseName_.set (x);
}

void FileWriterParametersType::
BaseName (::std::unique_ptr< BaseName_type > x)
{
  this->BaseName_.set (std::move (x));
}

const FileWriterParametersType::WriteFrequency_type& FileWriterParametersType::
WriteFrequency () const
{
  return this->WriteFrequency_.get ();
}

FileWriterParametersType::WriteFrequency_type& FileWriterParametersType::
WriteFrequency ()
{
  return this->WriteFrequency_.get ();
}

void FileWriterParametersType::
WriteFrequency (const WriteFrequency_type& x)
{
  this->WriteFrequency_.set (x);
}


// SimulationParametersType
//

const SimulationParametersType::EndT_type& SimulationParametersType::
EndT () const
{
  return this->EndT_.get ();
}

SimulationParametersType::EndT_type& SimulationParametersType::
EndT ()
{
  return this->EndT_.get ();
}

void SimulationParametersType::
EndT (const EndT_type& x)
{
  this->EndT_.set (x);
}

const SimulationParametersType::DeltaT_type& SimulationParametersType::
DeltaT () const
{
  return this->DeltaT_.get ();
}

SimulationParametersType::DeltaT_type& SimulationParametersType::
DeltaT ()
{
  return this->DeltaT_.get ();
}

void SimulationParametersType::
DeltaT (const DeltaT_type& x)
{
  this->DeltaT_.set (x);
}


// ThermostatParametersType
//

const ThermostatParametersType::StartTemperature_type& ThermostatParametersType::
StartTemperature () const
{
  return this->StartTemperature_.get ();
}

ThermostatParametersType::StartTemperature_type& ThermostatParametersType::
StartTemperature ()
{
  return this->StartTemperature_.get ();
}

void ThermostatParametersType::
StartTemperature (const StartTemperature_type& x)
{
  this->StartTemperature_.set (x);
}

const ThermostatParametersType::TargetTemperature_type& ThermostatParametersType::
TargetTemperature () const
{
  return this->TargetTemperature_.get ();
}

ThermostatParametersType::TargetTemperature_type& ThermostatParametersType::
TargetTemperature ()
{
  return this->TargetTemperature_.get ();
}

void ThermostatParametersType::
TargetTemperature (const TargetTemperature_type& x)
{
  this->TargetTemperature_.set (x);
}

const ThermostatParametersType::ApplyFrequency_type& ThermostatParametersType::
ApplyFrequency () const
{
  return this->ApplyFrequency_.get ();
}

ThermostatParametersType::ApplyFrequency_type& ThermostatParametersType::
ApplyFrequency ()
{
  return this->ApplyFrequency_.get ();
}

void ThermostatParametersType::
ApplyFrequency (const ApplyFrequency_type& x)
{
  this->ApplyFrequency_.set (x);
}

const ThermostatParametersType::MaxDeltaTemperature_type& ThermostatParametersType::
MaxDeltaTemperature () const
{
  return this->MaxDeltaTemperature_.get ();
}

ThermostatParametersType::MaxDeltaTemperature_type& ThermostatParametersType::
MaxDeltaTemperature ()
{
  return this->MaxDeltaTemperature_.get ();
}

void ThermostatParametersType::
MaxDeltaTemperature (const MaxDeltaTemperature_type& x)
{
  this->MaxDeltaTemperature_.set (x);
}

const ThermostatParametersType::Dimension_type& ThermostatParametersType::
Dimension () const
{
  return this->Dimension_.get ();
}

ThermostatParametersType::Dimension_type& ThermostatParametersType::
Dimension ()
{
  return this->Dimension_.get ();
}

void ThermostatParametersType::
Dimension (const Dimension_type& x)
{
  this->Dimension_.set (x);
}


// CuboidType
//

const CuboidType::Coordinates_type& CuboidType::
Coordinates () const
{
  return this->Coordinates_.get ();
}

CuboidType::Coordinates_type& CuboidType::
Coordinates ()
{
  return this->Coordinates_.get ();
}

void CuboidType::
Coordinates (const Coordinates_type& x)
{
  this->Coordinates_.set (x);
}

void CuboidType::
Coordinates (::std::unique_ptr< Coordinates_type > x)
{
  this->Coordinates_.set (std::move (x));
}

const CuboidType::ParticlesPerDimension_type& CuboidType::
ParticlesPerDimension () const
{
  return this->ParticlesPerDimension_.get ();
}

CuboidType::ParticlesPerDimension_type& CuboidType::
ParticlesPerDimension ()
{
  return this->ParticlesPerDimension_.get ();
}

void CuboidType::
ParticlesPerDimension (const ParticlesPerDimension_type& x)
{
  this->ParticlesPerDimension_.set (x);
}

void CuboidType::
ParticlesPerDimension (::std::unique_ptr< ParticlesPerDimension_type > x)
{
  this->ParticlesPerDimension_.set (std::move (x));
}

const CuboidType::Distance_type& CuboidType::
Distance () const
{
  return this->Distance_.get ();
}

CuboidType::Distance_type& CuboidType::
Distance ()
{
  return this->Distance_.get ();
}

void CuboidType::
Distance (const Distance_type& x)
{
  this->Distance_.set (x);
}

const CuboidType::Mass_type& CuboidType::
Mass () const
{
  return this->Mass_.get ();
}

CuboidType::Mass_type& CuboidType::
Mass ()
{
  return this->Mass_.get ();
}

void CuboidType::
Mass (const Mass_type& x)
{
  this->Mass_.set (x);
}

const CuboidType::InitialVelocities_type& CuboidType::
InitialVelocities () const
{
  return this->InitialVelocities_.get ();
}

CuboidType::InitialVelocities_type& CuboidType::
InitialVelocities ()
{
  return this->InitialVelocities_.get ();
}

void CuboidType::
InitialVelocities (const InitialVelocities_type& x)
{
  this->InitialVelocities_.set (x);
}

void CuboidType::
InitialVelocities (::std::unique_ptr< InitialVelocities_type > x)
{
  this->InitialVelocities_.set (std::move (x));
}

const CuboidType::MeanVelocity_type& CuboidType::
MeanVelocity () const
{
  return this->MeanVelocity_.get ();
}

CuboidType::MeanVelocity_type& CuboidType::
MeanVelocity ()
{
  return this->MeanVelocity_.get ();
}

void CuboidType::
MeanVelocity (const MeanVelocity_type& x)
{
  this->MeanVelocity_.set (x);
}


// Simulation
//

const Simulation::FileWriterParameters_type& Simulation::
FileWriterParameters () const
{
  return this->FileWriterParameters_.get ();
}

Simulation::FileWriterParameters_type& Simulation::
FileWriterParameters ()
{
  return this->FileWriterParameters_.get ();
}

void Simulation::
FileWriterParameters (const FileWriterParameters_type& x)
{
  this->FileWriterParameters_.set (x);
}

void Simulation::
FileWriterParameters (::std::unique_ptr< FileWriterParameters_type > x)
{
  this->FileWriterParameters_.set (std::move (x));
}

const Simulation::SimulationParameters_type& Simulation::
SimulationParameters () const
{
  return this->SimulationParameters_.get ();
}

Simulation::SimulationParameters_type& Simulation::
SimulationParameters ()
{
  return this->SimulationParameters_.get ();
}

void Simulation::
SimulationParameters (const SimulationParameters_type& x)
{
  this->SimulationParameters_.set (x);
}

void Simulation::
SimulationParameters (::std::unique_ptr< SimulationParameters_type > x)
{
  this->SimulationParameters_.set (std::move (x));
}

const Simulation::ThermostatParameters_type& Simulation::
ThermostatParameters () const
{
  return this->ThermostatParameters_.get ();
}

Simulation::ThermostatParameters_type& Simulation::
ThermostatParameters ()
{
  return this->ThermostatParameters_.get ();
}

void Simulation::
ThermostatParameters (const ThermostatParameters_type& x)
{
  this->ThermostatParameters_.set (x);
}

void Simulation::
ThermostatParameters (::std::unique_ptr< ThermostatParameters_type > x)
{
  this->ThermostatParameters_.set (std::move (x));
}

const Simulation::Cuboids_sequence& Simulation::
Cuboids () const
{
  return this->Cuboids_;
}

Simulation::Cuboids_sequence& Simulation::
Cuboids ()
{
  return this->Cuboids_;
}

void Simulation::
Cuboids (const Cuboids_sequence& s)
{
  this->Cuboids_ = s;
}


#include <xsd/cxx/xml/dom/parsing-source.hxx>

// FileWriterParametersType
//

FileWriterParametersType::
FileWriterParametersType (const BaseName_type& BaseName,
                          const WriteFrequency_type& WriteFrequency)
: ::xml_schema::type (),
  BaseName_ (BaseName, this),
  WriteFrequency_ (WriteFrequency, this)
{
}

FileWriterParametersType::
FileWriterParametersType (const FileWriterParametersType& x,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  BaseName_ (x.BaseName_, f, this),
  WriteFrequency_ (x.WriteFrequency_, f, this)
{
}

FileWriterParametersType::
FileWriterParametersType (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  BaseName_ (this),
  WriteFrequency_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void FileWriterParametersType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // BaseName
    //
    if (n.name () == "BaseName" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< BaseName_type > r (
        BaseName_traits::create (i, f, this));

      if (!BaseName_.present ())
      {
        this->BaseName_.set (::std::move (r));
        continue;
      }
    }

    // WriteFrequency
    //
    if (n.name () == "WriteFrequency" && n.namespace_ ().empty ())
    {
      if (!WriteFrequency_.present ())
      {
        this->WriteFrequency_.set (WriteFrequency_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!BaseName_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "BaseName",
      "");
  }

  if (!WriteFrequency_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "WriteFrequency",
      "");
  }
}

FileWriterParametersType* FileWriterParametersType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class FileWriterParametersType (*this, f, c);
}

FileWriterParametersType& FileWriterParametersType::
operator= (const FileWriterParametersType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->BaseName_ = x.BaseName_;
    this->WriteFrequency_ = x.WriteFrequency_;
  }

  return *this;
}

FileWriterParametersType::
~FileWriterParametersType ()
{
}

// SimulationParametersType
//

SimulationParametersType::
SimulationParametersType (const EndT_type& EndT,
                          const DeltaT_type& DeltaT)
: ::xml_schema::type (),
  EndT_ (EndT, this),
  DeltaT_ (DeltaT, this)
{
}

SimulationParametersType::
SimulationParametersType (const SimulationParametersType& x,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  EndT_ (x.EndT_, f, this),
  DeltaT_ (x.DeltaT_, f, this)
{
}

SimulationParametersType::
SimulationParametersType (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  EndT_ (this),
  DeltaT_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void SimulationParametersType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // EndT
    //
    if (n.name () == "EndT" && n.namespace_ ().empty ())
    {
      if (!EndT_.present ())
      {
        this->EndT_.set (EndT_traits::create (i, f, this));
        continue;
      }
    }

    // DeltaT
    //
    if (n.name () == "DeltaT" && n.namespace_ ().empty ())
    {
      if (!DeltaT_.present ())
      {
        this->DeltaT_.set (DeltaT_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!EndT_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "EndT",
      "");
  }

  if (!DeltaT_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "DeltaT",
      "");
  }
}

SimulationParametersType* SimulationParametersType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class SimulationParametersType (*this, f, c);
}

SimulationParametersType& SimulationParametersType::
operator= (const SimulationParametersType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->EndT_ = x.EndT_;
    this->DeltaT_ = x.DeltaT_;
  }

  return *this;
}

SimulationParametersType::
~SimulationParametersType ()
{
}

// ThermostatParametersType
//

ThermostatParametersType::
ThermostatParametersType (const StartTemperature_type& StartTemperature,
                          const TargetTemperature_type& TargetTemperature,
                          const ApplyFrequency_type& ApplyFrequency,
                          const MaxDeltaTemperature_type& MaxDeltaTemperature,
                          const Dimension_type& Dimension)
: ::xml_schema::type (),
  StartTemperature_ (StartTemperature, this),
  TargetTemperature_ (TargetTemperature, this),
  ApplyFrequency_ (ApplyFrequency, this),
  MaxDeltaTemperature_ (MaxDeltaTemperature, this),
  Dimension_ (Dimension, this)
{
}

ThermostatParametersType::
ThermostatParametersType (const ThermostatParametersType& x,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  StartTemperature_ (x.StartTemperature_, f, this),
  TargetTemperature_ (x.TargetTemperature_, f, this),
  ApplyFrequency_ (x.ApplyFrequency_, f, this),
  MaxDeltaTemperature_ (x.MaxDeltaTemperature_, f, this),
  Dimension_ (x.Dimension_, f, this)
{
}

ThermostatParametersType::
ThermostatParametersType (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  StartTemperature_ (this),
  TargetTemperature_ (this),
  ApplyFrequency_ (this),
  MaxDeltaTemperature_ (this),
  Dimension_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void ThermostatParametersType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // StartTemperature
    //
    if (n.name () == "StartTemperature" && n.namespace_ ().empty ())
    {
      if (!StartTemperature_.present ())
      {
        this->StartTemperature_.set (StartTemperature_traits::create (i, f, this));
        continue;
      }
    }

    // TargetTemperature
    //
    if (n.name () == "TargetTemperature" && n.namespace_ ().empty ())
    {
      if (!TargetTemperature_.present ())
      {
        this->TargetTemperature_.set (TargetTemperature_traits::create (i, f, this));
        continue;
      }
    }

    // ApplyFrequency
    //
    if (n.name () == "ApplyFrequency" && n.namespace_ ().empty ())
    {
      if (!ApplyFrequency_.present ())
      {
        this->ApplyFrequency_.set (ApplyFrequency_traits::create (i, f, this));
        continue;
      }
    }

    // MaxDeltaTemperature
    //
    if (n.name () == "MaxDeltaTemperature" && n.namespace_ ().empty ())
    {
      if (!MaxDeltaTemperature_.present ())
      {
        this->MaxDeltaTemperature_.set (MaxDeltaTemperature_traits::create (i, f, this));
        continue;
      }
    }

    // Dimension
    //
    if (n.name () == "Dimension" && n.namespace_ ().empty ())
    {
      if (!Dimension_.present ())
      {
        this->Dimension_.set (Dimension_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!StartTemperature_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "StartTemperature",
      "");
  }

  if (!TargetTemperature_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "TargetTemperature",
      "");
  }

  if (!ApplyFrequency_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "ApplyFrequency",
      "");
  }

  if (!MaxDeltaTemperature_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "MaxDeltaTemperature",
      "");
  }

  if (!Dimension_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "Dimension",
      "");
  }
}

ThermostatParametersType* ThermostatParametersType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class ThermostatParametersType (*this, f, c);
}

ThermostatParametersType& ThermostatParametersType::
operator= (const ThermostatParametersType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->StartTemperature_ = x.StartTemperature_;
    this->TargetTemperature_ = x.TargetTemperature_;
    this->ApplyFrequency_ = x.ApplyFrequency_;
    this->MaxDeltaTemperature_ = x.MaxDeltaTemperature_;
    this->Dimension_ = x.Dimension_;
  }

  return *this;
}

ThermostatParametersType::
~ThermostatParametersType ()
{
}

// CuboidType
//

CuboidType::
CuboidType (const Coordinates_type& Coordinates,
            const ParticlesPerDimension_type& ParticlesPerDimension,
            const Distance_type& Distance,
            const Mass_type& Mass,
            const InitialVelocities_type& InitialVelocities,
            const MeanVelocity_type& MeanVelocity)
: ::xml_schema::type (),
  Coordinates_ (Coordinates, this),
  ParticlesPerDimension_ (ParticlesPerDimension, this),
  Distance_ (Distance, this),
  Mass_ (Mass, this),
  InitialVelocities_ (InitialVelocities, this),
  MeanVelocity_ (MeanVelocity, this)
{
}

CuboidType::
CuboidType (const CuboidType& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  Coordinates_ (x.Coordinates_, f, this),
  ParticlesPerDimension_ (x.ParticlesPerDimension_, f, this),
  Distance_ (x.Distance_, f, this),
  Mass_ (x.Mass_, f, this),
  InitialVelocities_ (x.InitialVelocities_, f, this),
  MeanVelocity_ (x.MeanVelocity_, f, this)
{
}

CuboidType::
CuboidType (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  Coordinates_ (this),
  ParticlesPerDimension_ (this),
  Distance_ (this),
  Mass_ (this),
  InitialVelocities_ (this),
  MeanVelocity_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void CuboidType::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // Coordinates
    //
    if (n.name () == "Coordinates" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< Coordinates_type > r (
        Coordinates_traits::create (i, f, this));

      if (!Coordinates_.present ())
      {
        this->Coordinates_.set (::std::move (r));
        continue;
      }
    }

    // ParticlesPerDimension
    //
    if (n.name () == "ParticlesPerDimension" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< ParticlesPerDimension_type > r (
        ParticlesPerDimension_traits::create (i, f, this));

      if (!ParticlesPerDimension_.present ())
      {
        this->ParticlesPerDimension_.set (::std::move (r));
        continue;
      }
    }

    // Distance
    //
    if (n.name () == "Distance" && n.namespace_ ().empty ())
    {
      if (!Distance_.present ())
      {
        this->Distance_.set (Distance_traits::create (i, f, this));
        continue;
      }
    }

    // Mass
    //
    if (n.name () == "Mass" && n.namespace_ ().empty ())
    {
      if (!Mass_.present ())
      {
        this->Mass_.set (Mass_traits::create (i, f, this));
        continue;
      }
    }

    // InitialVelocities
    //
    if (n.name () == "InitialVelocities" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< InitialVelocities_type > r (
        InitialVelocities_traits::create (i, f, this));

      if (!InitialVelocities_.present ())
      {
        this->InitialVelocities_.set (::std::move (r));
        continue;
      }
    }

    // MeanVelocity
    //
    if (n.name () == "MeanVelocity" && n.namespace_ ().empty ())
    {
      if (!MeanVelocity_.present ())
      {
        this->MeanVelocity_.set (MeanVelocity_traits::create (i, f, this));
        continue;
      }
    }

    break;
  }

  if (!Coordinates_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "Coordinates",
      "");
  }

  if (!ParticlesPerDimension_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "ParticlesPerDimension",
      "");
  }

  if (!Distance_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "Distance",
      "");
  }

  if (!Mass_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "Mass",
      "");
  }

  if (!InitialVelocities_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "InitialVelocities",
      "");
  }

  if (!MeanVelocity_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "MeanVelocity",
      "");
  }
}

CuboidType* CuboidType::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class CuboidType (*this, f, c);
}

CuboidType& CuboidType::
operator= (const CuboidType& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->Coordinates_ = x.Coordinates_;
    this->ParticlesPerDimension_ = x.ParticlesPerDimension_;
    this->Distance_ = x.Distance_;
    this->Mass_ = x.Mass_;
    this->InitialVelocities_ = x.InitialVelocities_;
    this->MeanVelocity_ = x.MeanVelocity_;
  }

  return *this;
}

CuboidType::
~CuboidType ()
{
}

// Simulation
//

Simulation::
Simulation (const FileWriterParameters_type& FileWriterParameters,
            const SimulationParameters_type& SimulationParameters,
            const ThermostatParameters_type& ThermostatParameters)
: ::xml_schema::type (),
  FileWriterParameters_ (FileWriterParameters, this),
  SimulationParameters_ (SimulationParameters, this),
  ThermostatParameters_ (ThermostatParameters, this),
  Cuboids_ (this)
{
}

Simulation::
Simulation (::std::unique_ptr< FileWriterParameters_type > FileWriterParameters,
            ::std::unique_ptr< SimulationParameters_type > SimulationParameters,
            ::std::unique_ptr< ThermostatParameters_type > ThermostatParameters)
: ::xml_schema::type (),
  FileWriterParameters_ (std::move (FileWriterParameters), this),
  SimulationParameters_ (std::move (SimulationParameters), this),
  ThermostatParameters_ (std::move (ThermostatParameters), this),
  Cuboids_ (this)
{
}

Simulation::
Simulation (const Simulation& x,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (x, f, c),
  FileWriterParameters_ (x.FileWriterParameters_, f, this),
  SimulationParameters_ (x.SimulationParameters_, f, this),
  ThermostatParameters_ (x.ThermostatParameters_, f, this),
  Cuboids_ (x.Cuboids_, f, this)
{
}

Simulation::
Simulation (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
: ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
  FileWriterParameters_ (this),
  SimulationParameters_ (this),
  ThermostatParameters_ (this),
  Cuboids_ (this)
{
  if ((f & ::xml_schema::flags::base) == 0)
  {
    ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
    this->parse (p, f);
  }
}

void Simulation::
parse (::xsd::cxx::xml::dom::parser< char >& p,
       ::xml_schema::flags f)
{
  for (; p.more_content (); p.next_content (false))
  {
    const ::xercesc::DOMElement& i (p.cur_element ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (i));

    // FileWriterParameters
    //
    if (n.name () == "FileWriterParameters" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< FileWriterParameters_type > r (
        FileWriterParameters_traits::create (i, f, this));

      if (!FileWriterParameters_.present ())
      {
        this->FileWriterParameters_.set (::std::move (r));
        continue;
      }
    }

    // SimulationParameters
    //
    if (n.name () == "SimulationParameters" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< SimulationParameters_type > r (
        SimulationParameters_traits::create (i, f, this));

      if (!SimulationParameters_.present ())
      {
        this->SimulationParameters_.set (::std::move (r));
        continue;
      }
    }

    // ThermostatParameters
    //
    if (n.name () == "ThermostatParameters" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< ThermostatParameters_type > r (
        ThermostatParameters_traits::create (i, f, this));

      if (!ThermostatParameters_.present ())
      {
        this->ThermostatParameters_.set (::std::move (r));
        continue;
      }
    }

    // Cuboids
    //
    if (n.name () == "Cuboids" && n.namespace_ ().empty ())
    {
      ::std::unique_ptr< Cuboids_type > r (
        Cuboids_traits::create (i, f, this));

      this->Cuboids_.push_back (::std::move (r));
      continue;
    }

    break;
  }

  if (!FileWriterParameters_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "FileWriterParameters",
      "");
  }

  if (!SimulationParameters_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "SimulationParameters",
      "");
  }

  if (!ThermostatParameters_.present ())
  {
    throw ::xsd::cxx::tree::expected_element< char > (
      "ThermostatParameters",
      "");
  }
}

Simulation* Simulation::
_clone (::xml_schema::flags f,
        ::xml_schema::container* c) const
{
  return new class Simulation (*this, f, c);
}

Simulation& Simulation::
operator= (const Simulation& x)
{
  if (this != &x)
  {
    static_cast< ::xml_schema::type& > (*this) = x;
    this->FileWriterParameters_ = x.FileWriterParameters_;
    this->SimulationParameters_ = x.SimulationParameters_;
    this->ThermostatParameters_ = x.ThermostatParameters_;
    this->Cuboids_ = x.Cuboids_;
  }

  return *this;
}

Simulation::
~Simulation ()
{
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& u,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& u,
             ::xml_schema::error_handler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (const ::std::string& u,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      u, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Simulation_ (isrc, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xml_schema::error_handler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Simulation_ (isrc, h, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is);
  return ::Simulation_ (isrc, h, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& sid,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Simulation_ (isrc, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& sid,
             ::xml_schema::error_handler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::auto_initializer i (
    (f & ::xml_schema::flags::dont_initialize) == 0,
    (f & ::xml_schema::flags::keep_dom) == 0);

  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Simulation_ (isrc, h, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::std::istream& is,
             const ::std::string& sid,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
  return ::Simulation_ (isrc, h, f, p);
}

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& i,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xsd::cxx::tree::error_handler< char > h;

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& i,
             ::xml_schema::error_handler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (::xercesc::InputSource& i,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
    ::xsd::cxx::xml::dom::parse< char > (
      i, h, p, f));

  if (!d.get ())
    throw ::xsd::cxx::tree::parsing< char > ();

  return ::std::unique_ptr< ::Simulation > (
    ::Simulation_ (
      std::move (d), f | ::xml_schema::flags::own_dom, p));
}

::std::unique_ptr< ::Simulation >
Simulation_ (const ::xercesc::DOMDocument& doc,
             ::xml_schema::flags f,
             const ::xml_schema::properties& p)
{
  if (f & ::xml_schema::flags::keep_dom)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

    return ::std::unique_ptr< ::Simulation > (
      ::Simulation_ (
        std::move (d), f | ::xml_schema::flags::own_dom, p));
  }

  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (n.name () == "Simulation" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::Simulation > r (
      ::xsd::cxx::tree::traits< ::Simulation, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Simulation",
    "");
}

::std::unique_ptr< ::Simulation >
Simulation_ (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
             ::xml_schema::flags f,
             const ::xml_schema::properties&)
{
  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > c (
    ((f & ::xml_schema::flags::keep_dom) &&
     !(f & ::xml_schema::flags::own_dom))
    ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
    : 0);

  ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
  const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

  const ::xsd::cxx::xml::qualified_name< char > n (
    ::xsd::cxx::xml::dom::name< char > (e));

  if (f & ::xml_schema::flags::keep_dom)
    doc.setUserData (::xml_schema::dom::tree_node_key,
                     (c.get () ? &c : &d),
                     0);

  if (n.name () == "Simulation" &&
      n.namespace_ () == "")
  {
    ::std::unique_ptr< ::Simulation > r (
      ::xsd::cxx::tree::traits< ::Simulation, char >::create (
        e, f, 0));
    return r;
  }

  throw ::xsd::cxx::tree::unexpected_element < char > (
    n.name (),
    n.namespace_ (),
    "Simulation",
    "");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
