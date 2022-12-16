const mongoose = require('mongoose')


const Room = mongoose.model('Room',{
    room: {type: String, require: true}
})

module.exports = Room