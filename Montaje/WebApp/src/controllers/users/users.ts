import models from "../../models/Index.js";
import { userSchema } from "../../types/user.js";
import { hashSync } from "bcrypt";
import { Router } from "express";


const users = Router();

users.get("/", async (req, res, next) => {
    try {
        const users = await models.User.findAll();
        res.status(200).json(users);
    } catch (error) {
        next(error);
    }
});

users.get("/:id", async (req, res, next) => {
    try {
        const user = await models.User.findByPk(req.params.id);
        if (!user) {
            throw new Error(`User with id: ${req.params.id} not found`);
        }
        res.status(200).json(user);
    } catch (error) {
        next(error);
    }
});

users.post("/", async (req, res, next) => {
    try {
        const { username, password } = userSchema.parse(req.body);
        const newUser = new models.User({
            password: hashSync(password, 10),
            username
        });
        await newUser.save();
        res.status(201).json(newUser);
    } catch (error) {
        next(error);
    }
});

users.put("/:id", async (req, res, next) => {
    try {
        const user = await models.User.findByPk(req.params.id);
        if (!user) {
            throw new Error(`User with id: ${req.params.id} not found`);
        }
        const { username, password } = userSchema.parse(req.body);
        await user.update({
            password: hashSync(password, 10),
            username
        });
        res.status(200).json(user);
    } catch (error) {
        next(error);
    }
});

users.delete("/:id", async (req, res, next) => {
    try {
        const user = await models.User.findByPk(req.params.id);
        if (!user) {
            throw new Error(`User with id: ${req.params.id} not found`);
        }
        await user.destroy();
        res.status(204).send();
    } catch (error) {
        next(error);
    }
});

export default users;
