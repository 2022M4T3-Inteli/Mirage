const router = require('express').Router()
const controllerHome = require('../controllers/controllerHome')

router.get('/', controllerHome.index);

module.exports = router;