const router = require('express').Router()
const Room = require('../models/Room')


router.get('/', function (req, res){
    res.render('assignRoom'); 
})


//Rota de adição de dados no database
router.post('/', async(req, res) => {

// req,body
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

})


module.exports = router;