/* Generated from orogen/lib/orogen/templates/typekit/Opaques.cpp */

#include <vizkit3d_debug_drawings/typekit/OpaqueTypes.hpp>
#include <vizkit3d_debug_drawings/typekit/Opaques.hpp>
#include <vizkit3d_debug_drawings/commands/CommandBuffer.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <thread>
#include <iostream>


using namespace boost;

void orogen_typekits::fromIntermediate(boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>& real_type,
                                       const wrappers::CommandWrapper& intermediate)
{
    //rock-display calls from intermediate with empty intermediate. No idea why...
    //FIXME investigate further
    if(intermediate.binaryData.size() == 0)
        return;
    
    //FIXME avoid copy (see how envire does it)
    std::vector<char> buffer;
    buffer.insert(buffer.begin(), (char*)intermediate.binaryData.data(), (char*)(intermediate.binaryData.data() + intermediate.binaryData.size()));
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);
    
    try 
    {
        vizkit3dDebugDrawings::CommandBuffer* cmd;
        ia >> cmd;
        real_type.reset(cmd);
    }
    catch (const std::exception &exc)
    {
        std::cerr << "Error while deserializing debug drawing command: " << exc.what();
        return;
    }
    
    
}
 
void orogen_typekits::toIntermediate(wrappers::CommandWrapper& intermediate,
                                     const boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>& real_type)
{
    //rock-display calls toIntermediate with invalid real_type. No idea why.
    //FIXME investigate why this happens
    if(!real_type)
    {
        return;
    }
    
    //need to copy data because the CommandWrapper has to carry unsigned char because
    //corba cannot transport char. Char has to be used for streaming because boost stream is incompatible with unsigend char
    std::vector<char> buffer; //streaming only works with char buffers
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    vizkit3dDebugDrawings::CommandBuffer* cmd = real_type.get();
    try 
    {
        oa << cmd;
        os.flush();
    }
    catch (const std::exception &exc)
    {
        std::cout << "Error while serializing debug drawing command: " << exc.what() << std::endl;
        return;
    }
    
    //FIXME avoid copy (see how envire does it)
    intermediate.binaryData.insert(intermediate.binaryData.begin(),
                                   (unsigned char*)buffer.data(), (unsigned char*)(buffer.data() + buffer.size()));
}
