const router = require('express').Router()
const Tags = require('../models/Tags')

//Cadastrar uma nova tag    
router.get('/', function (req, res){
    res.render('assignTag');
});

//Rota de adição de dados no database
router.post('/', async(req, res) => {

    // req,body
    const {macAdress, asset, refreshRate} = req.body 
    const tags = {
        macAdress,
        asset,
        refreshRate
    }
    try { 

        await Tags.create(tags)

        res.status(201).json({message: 'Tag adcionada com sucesso!'})
        
        res.redirect('back')

    } catch(error){
        res.status(500).json({error: error})
    }

})

//Rota de leitura de todos os dados da database
router.get('/', async(req, res) => {

    try { 
        const tags = await Tags.find()
        
        res.status(200).json(tags)

    } catch(error){
        res.status(500).json({error: error})
    }

})

//Rota de leitura de dados específicos (id's) da database
router.get('/:id', async (req, res ) => {

    //extrair o dado da requisiçõa
    const id = req.params.id

    try{

        const tags = await Tags.findOne({_id: id})
        res.status(200).json(tags)


    } catch(error){
        res.status(500).json({error: error})
    }

})

//Rota de atualização (PATCH / PUT) da database 
router.patch('/:id', async (req, res ) => {

    //extrair o dado da requisiçõa
    const id = req.params.id

    const {macAdress, room, asset} = req.body

    const tags = {
        macAdress,
        room,
        asset
    }

    try{

        const updateTag = await Tags.updateOne({_id: id}, tags)
        if(updateTag.matchedCount === 0){
            res.status(422).json({message: 'A tag não foi encontrada'})
            return
        } 
        res.status(200).json(tags)   
        

    } catch(error){
        res.status(500).json({error: error})
    }

})

//Rota de exclusão da tag 
router.delete('/:id', async(req,res)=> {

    const id = req.params.id

    const tags = await Tags.findOne({_id: id})
    
    if(!tags){
        res.status(422).json({message: 'Tag não encontrada!'})
    }

    try{ 
        await Tags.deleteOne({_id: id})

        res.status(200).json({message: "Tag deletada com sucesso!"})
    }

    catch(error){ 
        res.status(500).json({error: error})
    }
})








module.exports = router;