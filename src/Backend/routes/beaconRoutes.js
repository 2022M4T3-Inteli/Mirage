const router = require('express').Router()

const Beacons = require('../models/Beacons')

//Rotas da API 

router.get('/', function(res){
    res.render('asssignBeacon')
})


router.post('/', async(req, res) => {

    // req,body
    const {idBeacon, room} = req.body

    const beacon = {
        idBeacon,
        room, 
    }
    
    try { 

        await Beacons.create(beacon)

        res.status(201).json({message: 'Beacon adcionado com sucesso!'})

    } catch(error){
        res.status(500).json({error: error})
    }

})

module.exports = router