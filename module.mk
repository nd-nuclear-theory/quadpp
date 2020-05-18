$(eval $(begin-module))

################################################################
# unit definitions
################################################################

module_units_h := quadpp
module_units_cpp-h := spline
# module_units_f :=
module_programs_cpp_test := spline_test

# module_programs_f :=
# module_generated :=

################################################################
# library creation flag
################################################################

$(eval $(library))

$(eval $(end-module))
