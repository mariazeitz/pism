// Copyright (C) 2011, 2012, 2013, 2014, 2015, 2016 PISM Authors
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <gsl/gsl_math.h>

#include "PA_delta_P.hh"
#include "base/util/PISMConfigInterface.hh"
#include "base/util/io/io_helpers.hh"
#include "base/util/pism_utilities.hh"

namespace pism {
namespace atmosphere {

Delta_P::Delta_P(IceGrid::ConstPtr g, AtmosphereModel* in)
  : PScalarForcing<AtmosphereModel,PAModifier>(g, in) {
  m_offset = NULL;

  m_option_prefix = "-atmosphere_delta_P";
  m_offset_name = "delta_P";
  m_offset = new Timeseries(*m_grid, m_offset_name, m_config->get_string("time_dimension_name"));
  m_offset->metadata().set_string("units", "kg m-2 second-1");
  m_offset->metadata().set_string("glaciological_units", "kg m-2 year-1");
  m_offset->metadata().set_string("long_name", "precipitation offsets");
  m_offset->dimension_metadata().set_string("units", m_grid->ctx()->time()->units_string());
}

Delta_P::~Delta_P()
{
  // empty
}

void Delta_P::init() {

  m_t = m_dt = GSL_NAN;  // every re-init restarts the clock

  m_input_model->init();

  m_log->message(2,
             "* Initializing precipitation forcing using scalar offsets...\n");

  init_internal();
}

MaxTimestep Delta_P::max_timestep_impl(double t) {
  (void) t;
  return MaxTimestep();
}

void Delta_P::init_timeseries(const std::vector<double> &ts) {
  PAModifier::init_timeseries(ts);

  m_offset_values.resize(m_ts_times.size());
  for (unsigned int k = 0; k < m_ts_times.size(); ++k) {
    m_offset_values[k] = (*m_offset)(m_ts_times[k]);
  }
}



void Delta_P::mean_precipitation(IceModelVec2S &result) {
  m_input_model->mean_precipitation(result);
  offset_data(result);
}

void Delta_P::precip_time_series(int i, int j, std::vector<double> &result) {
  m_input_model->precip_time_series(i, j, result);
  
  for (unsigned int k = 0; k < m_ts_times.size(); ++k) {
    result[k] += m_offset_values[k];
  }
}

void Delta_P::add_vars_to_output_impl(const std::string &keyword, std::set<std::string> &result) {
  m_input_model->add_vars_to_output(keyword, result);

  if (keyword == "medium" || keyword == "big" || keyword == "2dbig") {
    result.insert(m_air_temp.get_name());
    result.insert(m_precipitation.get_name());
  }
}


void Delta_P::define_variables_impl(const std::set<std::string> &vars_input, const PIO &nc,
                                            IO_Type nctype) {
  std::set<std::string> vars = vars_input;
  std::string order = m_config->get_string("output_variable_order");

  if (set_contains(vars, m_air_temp)) {
    io::define_spatial_variable(m_air_temp, *m_grid, nc, nctype, order, false);
    vars.erase(m_air_temp.get_name());
  }

  if (set_contains(vars, m_precipitation)) {
    io::define_spatial_variable(m_precipitation, *m_grid, nc, nctype, order, true);
    vars.erase(m_precipitation.get_name());
  }

  m_input_model->define_variables(vars, nc, nctype);
}


void Delta_P::write_variables_impl(const std::set<std::string> &vars_input, const PIO &nc) {
  std::set<std::string> vars = vars_input;

  if (set_contains(vars, m_air_temp)) {
    IceModelVec2S tmp;
    tmp.create(m_grid, m_air_temp.get_name(), WITHOUT_GHOSTS);
    tmp.metadata() = m_air_temp;

    mean_annual_temp(tmp);

    tmp.write(nc);

    vars.erase(m_air_temp.get_name());
  }

  if (set_contains(vars, m_precipitation)) {
    IceModelVec2S tmp;
    tmp.create(m_grid, m_precipitation.get_name(), WITHOUT_GHOSTS);
    tmp.metadata() = m_precipitation;

    mean_precipitation(tmp);

    tmp.write_in_glaciological_units = true;
    tmp.write(nc);

    vars.erase(m_precipitation.get_name());
  }

  m_input_model->write_variables(vars, nc);
}

} // end of namespace atmosphere
} // end of namespace pism
