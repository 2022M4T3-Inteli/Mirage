const router = require('express').Router()

router.get('/', function (req, res){
    res.render('search');
});

module.exports = router;