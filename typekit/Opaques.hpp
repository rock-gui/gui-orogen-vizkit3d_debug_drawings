/* Generated from orogen/lib/orogen/templates/typekit/Opaques.hpp */

#ifndef __OROGEN_GENERATED_vizkit3d_debug_drawings_USER_MARSHALLING_HH
#define __OROGEN_GENERATED_vizkit3d_debug_drawings_USER_MARSHALLING_HH

#include <vizkit3d_debug_drawings/typekit/OpaqueFwd.hpp>

namespace orogen_typekits
{
    
    /** Converts \c real_type into \c intermediate */
    void toIntermediate(::wrappers::CommandWrapper& intermediate, const boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>& real_type);
    /** Converts \c intermediate into \c real_type */
    void fromIntermediate(boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>& real_type, ::wrappers::CommandWrapper const& intermediate);
        
    
}

#endif

