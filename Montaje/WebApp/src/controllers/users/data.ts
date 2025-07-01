import models from "../../models/Index.js";
import { dataSchema } from "../../types/data.js";
import { Router } from "express";


const data = Router();

data.get("/", async (req, res, next) => {
    try {
        const data = await models.SensedData.findAll();
        res.status(200).json(data);
    } catch (error) {
        next(error);
    }
});

data.get("/:id", async (req, res, next) => {
    try {
        const data = await models.SensedData.findByPk(req.params.id);
        if (!data) {
            throw new Error(`Data entry with id: ${req.params.id} not found`);
        }
        res.status(200).json(data);
    } catch (error) {
        next(error);
    }
});

data.get("/ofDevice/:id", async (req, res, next) => {
    try {
        const data = await models.SensedData.findAll({
            where: { espId: req.params.id }
        });
        if (!data) {
            throw new Error(`Data entry with id: ${req.params.id} not found`);
        }
        res.status(200).json(data);
    } catch (error) {
        next(error);
    }
});

data.post("/", async (req, res, next) => {
    try {
        const newData = new models.SensedData(dataSchema.parse(req.body));
        await newData.save();
        res.status(201).json(newData);
    } catch (error) {
        next(error);
    }
});

data.put("/:id", async (req, res, next) => {
    try {
        const data = await models.SensedData.findByPk(req.params.id);
        if (!data) {
            throw new Error(`Data entry with id: ${req.params.id} not found`);
        }
        const newData = dataSchema.parse(req.body);
        await data.update(newData);
        res.status(200).json(data);
    } catch (error) {
        next(error);
    }
});

data.delete("/:id", async (req, res, next) => {
    try {
        const data = await models.SensedData.findByPk(req.params.id);
        if (!data) {
            throw new Error(`Data entry with id: ${req.params.id} not found`);
        }
        await data.destroy();
        res.status(204).send();
    } catch (error) {
        next(error);
    }
});

export default data;
