#ifndef XFIELDS_BEAMBEAM_H
#define XFIELDS_BEAMBEAM_H

/*gpufun*/
void BeamBeamBiGaussian2D_track_local_particle(
		BeamBeamBiGaussian2DData el, LocalParticle* part){

    BiGaussianFieldMapData fmap = BeamBeamBiGaussian2DData_getp_fieldmap(el);
    double const bb_q0 = BeamBeamBiGaussian2DData_get_q0(el);
    double const bb_n_particles = BeamBeamBiGaussian2DData_get_n_particles(el);
    double const bb_beta0 = BeamBeamBiGaussian2DData_get_beta0(el); 
 
    double const n_part = LocalParticle_get_num_particles(part); //only_for_context cpu_serial cpu_openmp
    for (int ii=0; ii<n_part; ii++){ //only_for_context cpu_serial cpu_openmp
        part->ipart = ii;            //only_for_context cpu_serial cpu_openmp

	double const x = LocalParticle_get_x(part);
	double const y = LocalParticle_get_y(part);
	double const part_q0 = LocalParticle_get_q0(part);
	double const part_mass0 = LocalParticle_get_mass0(part);
	double const part_chi = LocalParticle_get_chi(part);
	double const part_beta0 = LocalParticle_get_beta0(part);
	double const part_gamma0 = LocalParticle_get_gamma0(part);

   	double dphi_dx, dphi_dy;

	BiGaussianFieldMap_get_dphi_dx_dphi_dy(fmap, x, y,
                          &dphi_dx, &dphi_dy);

        const double charge_mass_ratio = part_chi*QELEM*part_q0
                    /(part_mass0*QELEM/(C_LIGHT*C_LIGHT));
        const double factor = -(charge_mass_ratio*bb_n_particles*bb_q0* QELEM
                    /(part_gamma0*part_beta0*C_LIGHT*C_LIGHT)
                    *(1+bb_beta0*part_beta0)/(bb_beta0 + part_beta0));

	LocalParticle_add_to_px(part, factor*dphi_dx);
	LocalParticle_add_to_py(part, factor*dphi_dy);

    } //only_for_context cpu_serial cpu_openmp

}

#endif