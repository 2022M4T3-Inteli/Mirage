const mongoose = require('mongoose')

const Tag = mongoose.model('Tag',{
    macAdress: {type: Number, require: true},
    asset: {type: String, require: true},
    refreshRate: {type: Number, require: true},
    relativePosition: {
        type: [0,0,0],
        default: undefined,
        require: false
    }
})

module.exports = Tag