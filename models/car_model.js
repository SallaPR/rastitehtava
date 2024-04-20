const db = require('../database.js');

const car = {
  getAll: function(callback) {
    return db.query('select * from car', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from car where id_car=?', [id], callback);
  },
  add: function(car, callback) {
    return db.query(
      'insert into car (brand,model) values(?,?)',
      [car.brand, car.model],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from car where id_car=?', [id], callback);
  },
  update: function(id, car, callback) {
    return db.query(
      'update car set brand=?, model=? where id_car=?',
      [car.brand, car.model, id],
      callback
    );
  }

};
module.exports = car;