// Model import
const Tags = require('../models/Tags');

exports.Tags = function(res, req){
    res.send('opa');
}

exports.createTag = function (req, res, next) {

    Tags.create(req.body).then(function(Tags){
    res.send(Tags);
    });
};

exports.readTag = function (req, res, next){
    Tags.find({}).then(function(Tags){
        res.send(Tags);
    });
}
exports.updateTag = function (req, res, next){
    // apaga ‘pi’ da BD, depois, devolve o ‘pi’ apagado ao cliente
    Tags.findByIdAndUpdate({_id: req.params.id},
        req.body).then(function(){
    Tags.findOne({_id: req.params.id}).then(function(Tags){
        res.send(Tags);
        });
    }).catch(next);
};

exports.deleteUpdate = function (req, res, next){
    Tags.findByIdAndRemove({_id: req.params.id}).then(function(Tags){
        res.send(Tags);
    }).catch(next);
};
