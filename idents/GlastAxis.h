#ifndef IDENTS_GLASTAXIS_H
#define IDENTS_GLASTAXIS_H 1

/**
 * @class GlastAxis
 *
 * @brief Provides a single source for the GLAST axis definition
 *
 * The class provides a GLAST-wide definition for the axes X and Y,
 * both X and Y, and one for when the concept of axis doesn't apply.
 *
 * Each subsystem should use this class when designation of an
 * axis is required, but how the axis is used will vary with the
 * context.
 *
 * For example, TkrRecon uses:
 *
 *   idents::GlastAxis::axis view
 *
 * to tell which co-oridinate the strip "views," and CalRecon uses:
 *
 *   idents::GlastAxis::axis orientation
 *
 * to tell how each log is "oriented."
 *
 * In both these cases, the name of the local variable defines the 
 * context.

 * @author Leon Rochester
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/idents/idents/GlastAxis.h,v 1.1 2002/01/30 01:18:37 lsrea Exp $
 */

namespace idents {
	
	class GlastAxis
	{
	public:
		
		enum axis {X, Y, XY, NONE};		
	};
	
}

#endif // IDENTS_GLASTAXIS

