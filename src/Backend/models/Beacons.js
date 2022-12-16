const mongoose = require('mongoose')

const Beacon = mongoose.model('Beacon',{
    macAdress: {type: Number, require: true},
    room: {type: String, require: true},
    position: {
        type: [0, 0],
        default: undefined,
        require: true
    }
})

module.exports = Beacon