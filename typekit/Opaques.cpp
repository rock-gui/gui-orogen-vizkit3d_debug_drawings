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

void orogen_typekits::fromIntermediate(boost::shared_ptr<vizkit3dDebugDrawings::Command>& real_type,
                                       const wrappers::CommandWrapper& intermediate)
{
    std::cout << "FROM INTERMEDIATE" << std::endl;
    std::cout << "size: " << intermediate.binaryData.size() << std::endl;
    
    //FIXME why does this happen?
    if(intermediate.binaryData.size() == 0)
        
        return;
    
    //FIXME avoid copy (see how envire does it)
    std::vector<char> buffer;
    buffer.insert(buffer.begin(), (char*)intermediate.binaryData.data(), (char*)(intermediate.binaryData.data() + intermediate.binaryData.size()));
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);
    
    if(!real_type)
        real_type.reset(new vizkit3dDebugDrawings::Command);
        
    ia >> *real_type;
    std::cout << "FROM INTERMEDIATE END" << std::endl;
}

void orogen_typekits::toIntermediate(wrappers::CommandWrapper& intermediate,
                                     const boost::shared_ptr<vizkit3dDebugDrawings::Command>& real_type)
{
    std::cout << "TO INTERMEDIATE" << std::endl;
//     need to copy data because the CommandWrapper has to carry unsigned char because
//     corba cannot transport char. Char has to be used for streaming because boost stream is incompatible with unsigend char
    std::vector<char> buffer; //streaming only works with char buffers
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    oa << *real_type;
    os.close(); //to flush
    //FIXME avoid copy (see how envire does it)
    intermediate.binaryData.insert(intermediate.binaryData.begin(),
                                   (unsigned char*)buffer.data(), (unsigned char*)(buffer.data() + buffer.size()));
    std::cout << "intermediate buffer size: " << intermediate.binaryData.size() << std::endl;
    std::cout << "TO INTERMEDIATE END" << std::endl;
}



// void orogen_typekits::toIntermediate(::wrappers::CommandWrapper& intermediate, boost::shared_ptr<vizkit3dDebugDrawings::Command>& real_type)
// {

//     
// }
// 
// void orogen_typekits::fromIntermediate(::vizkit3dDebugDrawings::Command& real_type, boost::shared_ptr<vizkit3dDebugDrawings::Command>& intermediate)
// {

// }

