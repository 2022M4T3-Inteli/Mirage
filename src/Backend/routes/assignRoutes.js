const router = require('express').Router()

router.get('/', function (req, res){
    res.render('assign');
});

module.exports = router;