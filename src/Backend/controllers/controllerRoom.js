const Room = require('../models/Room')

exports.newRoom =  async(req, res) => {

    // req body
        const {room} = req.body 
        const rooms = {
            room,
        }
        try { 
    
            await Room.create(rooms)
    
            res.status(201).json({message: 'Ae'})
    
        } catch(error){
            res.status(500).json({error: error})
        }
    
}

exports.deleteRoom = async(req, res, next) =>{


}   