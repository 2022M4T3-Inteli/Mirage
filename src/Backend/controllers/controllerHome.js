const controllerHome = {
    index: function(req, res, next){ 
        res.render('home');
    }
}

module.exports = controllerHome