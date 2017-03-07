/* Generated from orogen/lib/orogen/templates/typekit/Opaques.cpp */

#include <vizkit3d_debug_drawings/typekit/OpaqueTypes.hpp>
#include <vizkit3d_debug_drawings/typekit/Opaques.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>

    /** Returns the intermediate value that is contained in \c real_type */
    /** Stores \c intermediate into \c real_type. \c intermediate is owned by \c
     * real_type afterwards. */
    /** Release ownership of \c real_type on the corresponding intermediate
     * pointer.
     */

using namespace boost;

void orogen_typekits::toIntermediate(::wrappers::CommandWrapper& intermediate, ::vizkit3dDebugDrawings::Command const& real_type)
{
    std::vector<char> buffer; //streaming only works with char buffers
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    oa << real_type;
    os.close(); //to flush
    
    //FIXME avoid additional copy?!
    intermediate.binaryData.insert(intermediate.binaryData.begin(),
                                   (unsigned char*)buffer.data(), (unsigned char*)(buffer.data() + buffer.size()));
    
}

void orogen_typekits::fromIntermediate(::vizkit3dDebugDrawings::Command& real_type, ::wrappers::CommandWrapper const& intermediate)
{
    std::vector<char> buffer;
    buffer.insert(buffer.begin(), (char*)intermediate.binaryData.data(), (char*)(intermediate.binaryData.data() + intermediate.binaryData.size()));
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);
    ia >> real_type;
}

