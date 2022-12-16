const router = require('express').Router()

router.get('/', function (req, res){
    res.render('remove');
});

module.exports = router;